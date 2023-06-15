from weather_station.config import credentials, send_email
from weather_station.models import Weather
from flask_mail import Message
from weather_station import mail, db
from datetime import datetime

class Data:
    all_data = []
    
    def __init__(self):
        pass
    
    def send_email_f(self):
        if self.all_data[-1].get("temperature") > send_email.SEND_EMAIL_TEMPERATURE:
            msg = Message(send_email.EMAIL_TEMPERATURE_HEAD, sender=credentials.EMAIL, recipients=credentials.EMAIL_RECEIVERS)
            msg.body = send_email.EMAIL_TEMPERATURE_CONTENT.format(self.all_data[-1].get("temperature"))
            mail.send(msg)
            send_email.SEND_EMAIL_TEMPERATURE += 2
            print("Email sent")
    
    def store_data(self, app):
        with app.app_context():
            
            weather_data = Weather(values=self.all_data[-1], device="ESP32")
            current_time = datetime.now()
            if current_time.minute % 30 == 0:
                last_record = Weather.query.order_by(Weather.id.desc()).first()
                
                if last_record:
                    if current_time.strftime("%H:%M") != last_record.date.strftime("%H:%M"):
                        db.session.add(weather_data)
                        db.session.commit()
                    
                elif Weather.query.count() == 0:
                    db.session.add(weather_data)
                    db.session.commit()
