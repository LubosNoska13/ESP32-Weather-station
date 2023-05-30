from weather_station.config import credentials

class Config:
    # App config
    SECRET_KEY = credentials.SECRET_KEY
    SQLALCHEMY_DATABASE_URI = credentials.DATABASE_URI
    
    # Broker config
    MQTT_BROKER_URL = credentials.MQTT_BROKER_URL
    MQTT_BROKER_PORT = credentials.MQTT_BROKER_PORT 
    MQTT_USERNAME = credentials.MQTT_USERNAME  
    MQTT_PASSWORD = credentials.MQTT_PASSWORD  
    MQTT_KEEPALIVE = credentials.MQTT_KEEPALIVE  
    MQTT_TLS_ENABLED = credentials.MQTT_TLS_ENABLED  

    # Email config
    MAIL_SERVER = credentials.EMAIL_SERVER
    MAIL_PORT = credentials.EMAIL_PORT
    MAIL_USERNAME = credentials.EMAIL
    MAIL_PASSWORD = credentials.EMAIL_PASSWORD
    MAIL_USE_TLS = credentials.EMAIL_USE_TLS
    MAIL_USE_SSL = credentials.EMAIL_USE_SSL