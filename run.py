from weather_station import app

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5500, threaded=False, debug=True, use_reloader=True)