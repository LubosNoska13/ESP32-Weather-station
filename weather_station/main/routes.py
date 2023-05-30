from flask import Blueprint, render_template 
from flask_login import login_required

main = Blueprint("main", __name__)


@main.route("/")
@main.route("/home")
def home():
    return render_template("index.html", title="Home")


@main.route("/dashboard")
@login_required
def dashboard():
    return render_template("dashboard.html", title="Dashboard") 