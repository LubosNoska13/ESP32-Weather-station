// Get the date input element
const dateInput = document.querySelector('input[type="date"]');

let view_database_data = false;

// Add an event listener for the date input change
dateInput.addEventListener('change', () => {
    const selectedDate = dateInput.value;

    // Send an AJAX request to the Flask route to fetch the chart data
    fetch('/chart_data', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: `selected_date=${selectedDate}`
    })
        .then(response => response.json())
        .then(data => {
            // Update the chart with the fetched data
            view_database_data = true;
            updateCharts(data.values, data.labels, false);
            clearInterval(intervalID);
        })
        .catch(error => {
            console.error('Error:', error);
        });
});


function updateCharts(data, labels, real_time) {
  //==== Sort all data 
  console.log(data.Temperature)
  console.log(labels)
  const arr_temperature = data.map(item => item["Temperature"]);
  const arr_humidity = data.map(item => item["Humidity"]);
  const arr_wifi = data.map(item => item["Wifi"]);
  const arr_co = data.map(item => item["Carbon Monoxide"]);;
  const arr_co2 = data.map(item => item["arbon Dioxide"]);
  const arr_aceton = data.map(item => item["Aceton"]);
  const arr_alcohol = data.map(item => item["Alcohol"]);
  const arr_toluen = data.map(item => item["Toluen"]);
  const arr_nh4 = data.map(item => item["NH4"]);

  console.log(arr_temperature)

  if (real_time == true) {
    // Remove the oldest temperature and humidity if there are more than 7 elements
    if (arr_temperature.length > 7) {
      arr_temperature.shift();
      arr_humidity.shift();
      arr_wifi.shift();
      arr_co.shift();
      arr_aceton.shift();
      arr_alcohol.shift();
      arr_toluen.shift();
      arr_nh4.shift();
    }
  } else {
    //==== Update the charts
    chartTemperature.clear();
    chartHumidity.clear();
    chartWifi.clear();
    chartGases.clear();
  }
  //==== Update the chart data
  chartTemperature.data.datasets[0].data = arr_temperature;
  chartHumidity.data.datasets[0].data = arr_humidity;
  chartWifi.data.datasets[0].data = arr_wifi;
  chartGases.data.datasets[0].data = arr_co;
  chartGases.data.datasets[1].data = arr_co2;
  chartGases.data.datasets[2].data = arr_aceton;
  chartGases.data.datasets[3].data = arr_alcohol;
  chartGases.data.datasets[4].data = arr_toluen;
  chartGases.data.datasets[5].data = arr_nh4;

  //==== Set Labels
  if (real_time == true) {
    // Get the current time and format it using moment.js
    const currentTime = moment().format('HH:mm:ss');

    // Add the current time to the chart labels array
    chartTemperature.data.labels.push(currentTime);
    chartHumidity.data.labels.push(currentTime);
    chartWifi.data.labels.push(currentTime);
    chartGases.data.labels.push(currentTime);

    // Remove the oldest label if there are more than 10 labels
    if (chartTemperature.data.labels.length > 7) {
        chartTemperature.data.labels.shift();
        chartHumidity.data.labels.shift();
        chartWifi.data.labels.shift();
        chartGases.data.labels.shift();
    }
  } else {
    // Add the current time to the chart labels array
    chartTemperature.data.labels = labels;
    chartHumidity.data.labels = labels;
    chartWifi.data.labels = labels;
    chartGases.data.labels = labels;
  }

  //==== Update the charts
  chartTemperature.update();
  chartHumidity.update();
  chartWifi.update();
  chartGases.update();
}

function RealTimeData() {
  fetch('/esp32/data')
    .then(response => response.json())
      .then(data => {
        updateCharts(data, labels=[], real_time=true);
      });
}

// Set an interval to call the updateChart function every 4 seconds
if (view_database_data == false) {
  var intervalID = setInterval(RealTimeData, 4000);
} else {
  clearInterval(intervalID);
}

// Configure the initial chart using Chart.js
const TemperatureData = {
    labels: [],
    datasets: [{
    label: 'Temperature',
    borderWidth: 3,
    fill: true,
    data: [],
    backgroundColor: 'rgba(255, 99, 132, 0.5)', // Bar colorolor
    borderColor: 'rgba(255, 99, 132, 1)', // Border color
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
    data: [],
    backgroundColor: 'rgba(255, 152, 0, 0.5)', // Bar colorolor
    borderColor: '#E65100', // Border color
  }]
};

const CoData = {
  label: "CO",
  data: [],
  borderWidth: 3,
  fill: true,
  type: 'line',
  backgroundColor: 'rgba(54, 162, 235, 0.5)', // Bar color
  borderColor: 'rgba(54, 162, 235, 1)', // Border color
};

const Co2Data = {
  label: "CO2",
  data: [],
  borderWidth: 3,
  fill: true,
  type: 'line',
  backgroundColor: 'rgba(255, 99, 132, 0.5)', // Bar colorolor
  borderColor: 'rgba(255, 99, 132, 1)', // Border color
}

const AcetonData = {
  label: "Aceton",
  data: [],
  borderWidth: 3,
  fill: true,
  type: 'line',
  backgroundColor: 'rgba(76, 175, 80, 0.5)', // Bar colorolor
  borderColor: '#2E7D32', // Border color
}

const AlcoholData = {
  label: "Alcohol",
  data: [],
  borderWidth: 3,
  fill: true,
  type: 'line',
  backgroundColor: 'rgba(156, 39, 176, 0.5)', // Bar colorolor
  borderColor: '#4A148C', // Border color
}

const ToluenData = {
  label: "Toluen",
  data: [],
  borderWidth: 3,
  fill: true,
  type: 'line',
  backgroundColor: 'rgba(255, 152, 0, 0.5)', // Bar colorolor
  borderColor: '#E65100', // Border color
}

const Nh4Data = {
  label: "NH4",
  data: [],
  borderWidth: 3,
  fill: true,
  type: 'line',
  backgroundColor: 'rgba(233, 30, 99, 0.5)', // Bar colorolor
  borderColor: '#880E4F', // Border color
}


const chartGases = new Chart(document.getElementById('gasesChart').getContext('2d'), {
  type: 'line',
    data: {
        labels: [], // Sample labels
        datasets: [CoData, Co2Data, AcetonData, AlcoholData, ToluenData, Nh4Data]
    },
    options: {
      radius: 4,
      hitRadius: 30,
      hoverRadius: 8,
      responsive: true,
      tension: 0.4,
      scales: {
      x: [{
        ticks: {
          maxTicksLimit: 7
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
          maxTicksLimit: 7
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
            maxTicksLimit: 7
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
            maxTicksLimit: 7
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