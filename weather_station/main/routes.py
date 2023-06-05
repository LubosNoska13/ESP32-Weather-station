from flask import Blueprint, render_template 
from flask_login import login_required
from weather_station.models import Weather

main = Blueprint("main", __name__)


@main.route("/")
@main.route("/home")
def home():
    return render_template("index.html", title="Home")


@main.route("/dashboard")
@login_required
def dashboard():
    return render_template("dashboard.html", title="Dashboard") 

@main.route("/data")
@login_required
def data():
    database = Weather.query.order_by(Weather.id)
    return render_template("data.html", database=database)