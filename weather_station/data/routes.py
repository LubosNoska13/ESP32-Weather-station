from flask import Blueprint, render_template
from flask_login import login_required

data = Blueprint("data", __name__)

@data.route("/weather")
def weather():    
    return render_template("weather.html", title="Weather")

@data.route("/devices")
@login_required
def devices():
    return render_template("devices.html", title="Devices")