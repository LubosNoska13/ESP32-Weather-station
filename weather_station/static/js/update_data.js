
const temperatureSpan = document.querySelector("#stream-temperature-value");
const humiditySpan = document.querySelector("#stream-humidity-value");

function updateValues() {
    fetch('/esp32/data')
        .then(response => response.json())
        .then(data => {
        
        const temperature = parseFloat(data.pop()["temperature"].toFixed(2));
        const humidity = data.pop()["humidity"];
        console.log("Hello")
        temperatureSpan.innerHTML = temperature;
        humiditySpan.innerHTML = humidity;
        
    });
}
updateValues()
setInterval(updateValues, 3500);
