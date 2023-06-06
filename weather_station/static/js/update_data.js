
const temperatureSpan = document.querySelector("#stream-temperature-value");
const humiditySpan = document.querySelector("#stream-humidity-value");
const co2Span = document.querySelector("#stream-co2-value");
const coSpan = document.querySelector("#stream-co-value");
const acetonSpan = document.querySelector("#stream-aceton-value");
const alcoholSpan = document.querySelector("#stream-alcohol-value");
const nh4Span = document.querySelector("#stream-nh4-value");
const toluenSpan = document.querySelector("#stream-toluen-value");

function updateValues() {
    fetch('/esp32/data')
        .then(response => response.json())
        .then(data => {
        
        const temperature = parseFloat(data.pop()["temperature"].toFixed(2));
        const humidity = data.pop()["humidity"];
        const co2 = parseInt(data.pop()["co2"]);
        const co = data.pop()["co"]
        const aceton = data.pop()["aceton"]
        const alcohol = data.pop()["alcohol"]
        const nh4 = data.pop()["nh4"]
        const toluen = data.pop()["toluen"]
        
        temperatureSpan.innerHTML = temperature;
        humiditySpan.innerHTML = humidity;
        co2Span.innerHTML = co2;
        coSpan.innerHTML = co;
        acetonSpan.innerHTML = aceton;
        alcoholSpan.innerHTML = alcohol;
        nh4Span.innerHTML = nh4;
        toluenSpan.innerHTML = toluen;
    });
}
updateValues()
setInterval(updateValues, 3500);
