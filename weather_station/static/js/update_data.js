
const temperatureSpan = document.querySelector("#stream-temperature-value");
const humiditySpan = document.querySelector("#stream-humidity-value");
const co2Span = document.querySelector("#stream-co2-value");

function updateValues() {
    fetch('/esp32/data')
        .then(response => response.json())
        .then(data => {
        
        const temperature = parseFloat(data.pop()["temperature"].toFixed(2));
        const humidity = data.pop()["humidity"];
        const co2 = parseInt(data.pop()["co2"]);
        
        temperatureSpan.innerHTML = temperature;
        humiditySpan.innerHTML = humidity;
        co2Span.innerHTML = co2;
        
    });
}
updateValues()
setInterval(updateValues, 3500);
