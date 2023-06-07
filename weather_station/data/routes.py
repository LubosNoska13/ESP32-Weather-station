from flask import Blueprint, render_template, request, jsonify
from flask_login import login_required
from weather_station.models import Weather
from datetime import datetime, timedelta

data = Blueprint("data", __name__)

@data.route("/weather")
@login_required
def weather():    
    return render_template("weather.html", title="Weather")

@data.route("/devices")
@login_required
def devices():
    return render_template("devices.html", title="Devices")


@data.route('/chart_data', methods=['POST', 'GET'])
def chart_data():
    selected_date = request.form['selected_date']
    selected_date = datetime.strptime(selected_date, '%Y-%m-%d')
    
    next_date = selected_date + timedelta(days=1)
    print(selected_date)
    data = Weather.query.filter(Weather.date >= selected_date, Weather.date < next_date).all()
    
    # Format the data for the chart
    labels = [item.date.strftime('%H:%M') for item in data]
    values = [item.values for item in data]
    print({'labels': labels, 'values': values})
    # Return the data as JSON
    return jsonify({'labels': labels, 'values': values})