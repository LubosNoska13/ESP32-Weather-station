
// Define a function to fetch new data and update the chart
// Define a function to fetch new data and update the chart
function updateCharts() {
    fetch('/esp32/data')
      .then(response => response.json())
      .then(data => {
        const arr_temperature = data.map(item => item.temperature);
        const arr_humidity = data.map(item => item.humidity);
        const arr_wifi = data.map(item => item.wifi);

        // console.log(arr_temperature)
        // Remove the oldest temperature and humidity if there are more than 10 elements
        if (arr_temperature.length > 7) {
            arr_temperature.shift();
            arr_humidity.shift();
            arr_wifi.shift();
        }
        
        // Update the chart data
        // console.log(chartTemperature.data.datasets[0].data)
        chartTemperature.data.datasets[0].data = arr_temperature;
        chartHumidity.data.datasets[0].data = arr_humidity;
        chartWifi.data.datasets[0].data = arr_wifi;

        // Get the current time and format it using moment.js
        const currentTime = moment().format('HH:mm:ss');

        // Add the current time to the chart labels array
        chartTemperature.data.labels.push(currentTime);
        chartHumidity.data.labels.push(currentTime);
        chartWifi.data.labels.push(currentTime);

        // Remove the oldest label if there are more than 10 labels
        if (chartTemperature.data.labels.length > 7) {
            chartTemperature.data.labels.shift();
            chartHumidity.data.labels.shift();
            chartWifi.data.labels.shift();
        }
        // Update the charts
        chartTemperature.update();
        chartHumidity.update();
        chartWifi.update();
      });
  }


// Set an interval to call the updateChart function every 4 seconds
setInterval(updateCharts, 4000);

// Configure the initial chart using Chart.js
const TemperatureData = {
    labels: [],
    datasets: [{
    label: 'Temperature',
    borderWidth: 3,
    fill: true,
    data: []
  }]
};
const HumidityData = {
    labels: [],
    datasets: [{
    label: 'Humidity',
    borderWidth: 3,
    fill: true,
    data: []
  }]
};
const WifiData = {
    labels: [],
    datasets: [{
    label: 'Wifi signal strength',
    borderWidth: 3,
    fill: true,
    data: []
  }]
};

// Render the chart using Chart.js
const chartTemperature = new Chart(document.getElementById('temperatureChart').getContext('2d'), {
  type: 'line',
  data: TemperatureData,
  options: {

    radius: 4,
    hitRadius: 30,
    hoverRadius: 8,
    responsive: true,
    tension: 0.4,
    scales: {
      x: [{
        ticks: {
          maxTicksLimit: 10
        }
      }],
      y: [{
        ticks: {
          beginAtZero: true
        }
      }]
    },
    animation: {
            onComplete: () => {
                delayed = true;
            },
            delay: (context) => {
                let delay = 0;
                if (context.type === 'data' && context.mode === 'default' && !delayed) {
                delay = context.dataIndex * 300 + context.datasetIndex * 100;
                }
                return delay;
            },
        },
  }
});

// Render the chart using Chart.js
const chartHumidity = new Chart(document.getElementById('humidityChart').getContext('2d'), {
    type: 'line',
    data: HumidityData,
    options: {
  
      radius: 4,
      hitRadius: 30,
      hoverRadius: 8,
      responsive: true,
      tension: 0.4,
      scales: {
        x: [{
          ticks: {
            maxTicksLimit: 10
          }
        }],
        y: [{
          ticks: {
            beginAtZero: true
          }
        }]
      },
      animation: {
              onComplete: () => {
                  delayed = true;
              },
              delay: (context) => {
                  let delay = 0;
                  if (context.type === 'data' && context.mode === 'default' && !delayed) {
                  delay = context.dataIndex * 300 + context.datasetIndex * 100;
                  }
                  return delay;
              },
          },
    }
  });

//   Render the chart using Chart.js
const chartWifi = new Chart(document.getElementById('wifiChart').getContext('2d'), {
    type: 'line',
    data: WifiData,
    options: {
  
      radius: 4,
      hitRadius: 30,
      hoverRadius: 8,
      responsive: true,
      tension: 0.4,
      scales: {
        x: [{
          ticks: {
            maxTicksLimit: 10
          }
        }],
        y: [{
          ticks: {
            beginAtZero: true
          }
        }]
      },
      animation: {
              onComplete: () => {
                  delayed = true;
              },
              delay: (context) => {
                  let delay = 0;
                  if (context.type === 'data' && context.mode === 'default' && !delayed) {
                  delay = context.dataIndex * 300 + context.datasetIndex * 100;
                  }
                  return delay;
              },
          },
    }
  });