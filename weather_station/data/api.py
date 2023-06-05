import json
from flask import Blueprint, jsonify, current_app
from weather_station import mqtt, mail
from flask_mail import Message
from weather_station.config import credentials, send_email
from weather_station.models import Weather
from weather_station import db
from datetime import datetime
from weather_station.data.classes import Data

api = Blueprint("api", __name__)


@api.route('/esp32/data')
def data_esp32():
    return jsonify(Data.all_data)
