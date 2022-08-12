const getRatio = (type) => {
  if (type.includes("NACA")) {
    return parseFloat(type.slice(-2)) / 100.0
  } else if (type.includes("ELLIPSE")) {
    const a = type[type.length - 2];
    const b = type[type.length - 1];
    return parseFloat(b) / parseFloat(a);
  }
};

const getNacaCoords = (t) => {
  const computeY = (t, x) => {
    return (
      5 *
      t *
      (0.2969 * Math.pow(x, 0.5) -
        0.126 * x -
        0.3516 * Math.pow(x, 2.0) +
        0.2843 * Math.pow(x, 3.0) -
        0.105 * Math.pow(x, 4.0))
    );
  };

  const numPoints = 1000;

  const points = [];
  for (let i = 0; i < numPoints; i++) {
    const xx = i * (1.0 / numPoints);
    points.push({
      x: xx,
      y: computeY(t, xx),
    });
  }

  for (let i = 0; i < numPoints; i++) {
    const xx = i * (1.0 / numPoints);
    points.push({
      x: xx,
      y: -computeY(t, xx),
    });
  }

  return points;
};

const getCoordinates = geometryType => {
  const ratio = getRatio(geometryType);
  return getNacaCoords(ratio);
};

const updateGeometryChart = (chart, geometryType) => {
  const points = getCoordinates(geometryType);
  const data = {
    datasets: [
      {
        label: "Scatter Dataset",
        data: points,
        backgroundColor: "rgb(255, 99, 132)",
      },
    ],
  };

  const config = {
    type: "scatter",
    data: data,
    options: {
      responsive: false,
      showLine: true,
      scales: {
        x: {
          type: "linear",
          position: "bottom",
        },
      },
    },
  };

  new Chart(chart, config);
};

export default updateGeometryChart;
