import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.execute(
        "SELECT name,symbol,price,sum(shares) as sumshares FROM orders WHERE user_id = ? GROUP BY symbol",
        user_id,
    )
    dic1ele = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = dic1ele[0]["cash"]
    totalassets = cash
    for stock in stocks:
        total = stock["sumshares"] * stock["price"]  # 每一个股的总价值
        totalassets += total
    return render_template(
        "index.html", stocks=stocks, cash=cash, totalassets=totalassets, usd=usd
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol").upper()
        result = lookup(symbol)
        try:
            shares = float(request.form.get("shares"))
            if shares <= 0 or shares != int(shares):
                raise ValueError
            shares = int(shares)
        except ValueError:
            return apology("Please type in a positive integer for shares")
        if not symbol:
            return apology("Please type in the symbol")
        if not result:
            return apology("Can't find the stock")

        user_id = session["user_id"]
        dic1ele = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = dic1ele[0]["cash"]
        price = result["price"]
        total = price * shares
        if cash < price:
            return apology("No enough cash")
        else:
            balance = cash - total
            db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)
            db.execute(
                "INSERT INTO orders(user_id,name,symbol,shares,price,type) VALUES(?,?,?,?,?,?)",
                user_id,
                result["name"],
                symbol,
                shares,
                price,
                "buy",
            )

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    orders = db.execute(
        "SELECT type, symbol, price, shares, dertime FROM orders WHERE user_id = ?",
        user_id,
    )
    return render_template("history.html", orders=orders, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        result = lookup(symbol)
        if result:
            price = usd(result["price"])
            return render_template("quoted.html", result=result, price=price)
        else:
            return apology("Can't find the stock")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Must provide username")
        if not password:
            return apology("Must provide password")
        if not confirmation:
            return apology("Must confirm password")
        if password != confirmation:
            return apology("Passwords don't match")

        hash = generate_password_hash(password)

        if db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("Username already taken")

        db.execute("INSERT INTO users(username,hash) VALUES(?,?)", username, hash)
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbols = db.execute(
            "SELECT symbol FROM orders WHERE user_id = ? GROUP BY symbol", user_id
        )
        return render_template("sell.html", symbol=symbols)

    else:
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        rows = db.execute(
            "SELECT symbol FROM orders WHERE user_id = ? GROUP BY symbol", user_id
        )
        symbols = [row["symbol"] for row in rows]

        if not symbol:
            return apology("Please type in the symbol you wanna sell")
        if symbol not in symbols:
            return apology("You don't own this stock")

        try:
            shares = float(request.form.get("shares"))
            if shares <= 0 or shares != int(shares):
                raise ValueError
            shares = int(shares)
        except ValueError:
            return apology("Please type in a positive integer for shares")

        rows = db.execute(
            "SELECT sum(shares) as sumshares FROM orders WHERE user_id = ? AND symbol = ? ",
            user_id,
            symbol,
        )
        sharesowned = rows[0]["sumshares"] if rows else 0
        if sharesowned < shares:
            return apology("You don't have so many shares")

        price = lookup(symbol)["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        cash = price * shares + cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)
        db.execute(
            "INSERT INTO orders(user_id,name,symbol,shares,price,type) VALUES(?,?,?,?,?,?)",
            user_id,
            lookup(symbol)["name"],
            symbol,
            -shares,
            price,
            "sell",
        )

        return redirect("/")
