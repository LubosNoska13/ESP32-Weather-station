from weather_station import create_app
import json

app = create_app()

from weather_station import mqtt
from weather_station.data.classes import Data
d = Data()
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
        if len(d.all_data) > 7:
            d.all_data.pop(0)
        
        # Append the received data to the data_list
        d.all_data.append(data)
        
        d.store_data(app)
    
if __name__ == "__main__":
    # Create a database
    # from weather_station import db
    # with app.app_context():
        # db.create_all()
    app.run(host="0.0.0.0", port=5500, threaded=False, debug=True, use_reloader=False)