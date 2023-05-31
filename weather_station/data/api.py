import json
from flask import Blueprint, jsonify 
from weather_station import mqtt, mail
from flask_mail import Message
from weather_station.config import credentials, send_email
from weather_station.models import Weather
from weather_station import db

api = Blueprint("api", __name__)

data_list = []

@mqtt.on_message()
def on_message(client, userdata, message):
    # Extract the subscription topic from the message
    topic = message.topic
    
    if topic == "esp32/data":
        
        # Process the received message
        payload = message.payload.decode("utf-8")
        data = json.loads(payload)
        
        # print(data)
        
        # Only return the most recent 7 records
        if len(data_list) > 7:
            data_list.pop(0)
        
        # Append the received data to the data_list
        data_list.append(data)


def send_email(data):
    if data[-1].get("temperature") > send_email.SEND_EMAIL_TEMPERATURE:
        msg = Message(send_email.EMAIL_TEMPERATURE_HEAD, sender=credentials.EMAIL, recipients=credentials.EMAIL_RECEIVERS)
        msg.body = send_email.EMAIL_TEMPERATURE_CONTENT.format(data[-1].get("temperature"))
        mail.send(msg)
        send_email.SEND_EMAIL_TEMPERATURE += 1
        print("Email sent")

@api.route('/esp32/data')
def data_esp32():
    
    if len(data_list) >= 1:
        # Send Email
        send_email(data_list)

        print(data_list[-1])
        weather_data = Weather(values=data_list[-1], device="ESP32")
        
        # Add data to dabase
        db.session.add(weather_data)
        db.session.commit()
    return jsonify(data_list)
