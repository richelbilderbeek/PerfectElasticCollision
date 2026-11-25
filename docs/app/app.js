// PerfectElasticCollision, browser front-end for the WebAssembly core.
// Mirrors QtPerfectElasticCollisionMainDialog::paintEvent.
// Angles: clockwise, 12 o'clock is 0.
"use strict";

(function () {
  const ids = ["angle_impulse1", "speed_impulse1", "angle_collision", "angle_impulse2", "speed_impulse2"];
  const inputs = {};
  ids.forEach(function (id) { inputs[id] = document.getElementById(id); });
  const canvas = document.getElementById("canvas");
  const ctx = canvas.getContext("2d");
  const status = document.getElementById("status");
  const demo = document.getElementById("demo");
  const errorBox = document.getElementById("error");

  let collide = null;
  let getResult = null;

  function degToRad(d) { return d * Math.PI / 180.0; }

  function updateOutputs() {
    ids.forEach(function (id) {
      const out = document.querySelector('output[for="' + id + '"]');
      out.textContent = inputs[id].value + (id.indexOf("angle") === 0 ? "°" : "");
    });
  }

  function drawGlobe(x, y, radius, r, g, b) {
    // Bright rim, dark center, like the original DrawGlobe
    const grad = ctx.createRadialGradient(x, y, 0, x, y, radius);
    grad.addColorStop(0, "rgb(0,0,0)");
    grad.addColorStop(1, "rgb(" + r + "," + g + "," + b + ")");
    ctx.fillStyle = grad;
    ctx.beginPath();
    ctx.arc(x, y, radius, 0, 2 * Math.PI);
    ctx.fill();
  }

  function drawImpulse(x, y, angle, length, color, text) {
    const ex = x + Math.sin(angle) * length;
    const ey = y - Math.cos(angle) * length;
    ctx.strokeStyle = color;
    ctx.fillStyle = color;
    ctx.lineWidth = 3;
    ctx.beginPath();
    ctx.moveTo(x, y);
    ctx.lineTo(ex, ey);
    ctx.stroke();
    ctx.fillText(text, ex + 2, ey + 12);
  }

  function draw() {
    updateOutputs();
    if (!collide) return;

    const size = canvas.width;
    const scale = size / 250.0; // the impulse lengths are in 'Qt pixels', for a ~250px widget
    const angle = degToRad(+inputs.angle_collision.value);
    const angle1 = degToRad(+inputs.angle_impulse1.value);
    const angle2 = degToRad(+inputs.angle_impulse2.value);
    const speed1 = +inputs.speed_impulse1.value;
    const speed2 = +inputs.speed_impulse2.value;

    const globeSize = size / 5;
    const dx = Math.sin(angle) * globeSize;
    const dy = -Math.cos(angle) * globeSize;
    const mid = size / 2;
    const x1 = mid - dx / 2, y1 = mid - dy / 2;
    const x2 = mid + dx / 2, y2 = mid + dy / 2;

    ctx.fillStyle = "#010101";
    ctx.fillRect(0, 0, size, size);
    drawGlobe(x1, y1, globeSize / 2, 255, 0, 0);
    drawGlobe(x2, y2, globeSize / 2, 0, 0, 255);

    ctx.font = (12 * scale / 1.5) + "px system-ui, sans-serif";
    drawImpulse(x1, y1, angle1, speed1 * scale, "#fff", "before1");
    drawImpulse(x2, y2, angle2, speed2 * scale, "#fff", "before2");

    // The calculation is done in WebAssembly
    collide(angle, angle1, speed1, angle2, speed2);
    const newAngle1 = getResult(0);
    const newSpeed1 = getResult(1);
    const newAngle2 = getResult(2);
    const newSpeed2 = getResult(3);

    drawImpulse(x1, y1, newAngle1, newSpeed1 * scale, "#999", "after1");
    drawImpulse(x2, y2, newAngle2, newSpeed2 * scale, "#999", "after2");

    const before = speed1 + speed2;
    const after = newSpeed1 + newSpeed2;
    status.textContent = before > 0
      ? "Impulse change: " + ((after - before) / before * 100.0).toFixed(2) + "%"
      : "Impulse change: -";
  }

  ids.forEach(function (id) { inputs[id].addEventListener("input", draw); });

  // Demo mode: slowly rotate the dials, like the Qt version's timer
  let timer = null;
  function step(input, max_step) {
    const max = +input.max + 1;
    input.value = (+input.value + Math.floor(Math.random() * max_step)) % max;
  }
  demo.addEventListener("change", function () {
    if (demo.checked) {
      timer = setInterval(function () {
        step(inputs.angle_collision, 2);
        step(inputs.angle_impulse1, 3);
        step(inputs.angle_impulse2, 4);
        draw();
      }, 30);
    } else {
      clearInterval(timer);
      timer = null;
    }
  });

  updateOutputs();

  if (typeof createPerfectElasticCollisionModule !== "function") {
    errorBox.hidden = false;
    errorBox.textContent = "Could not load the WebAssembly module.";
    status.textContent = "";
    return;
  }
  createPerfectElasticCollisionModule().then(function (Module) {
    collide = Module.cwrap("pec_collide", null, ["number", "number", "number", "number", "number"]);
    getResult = Module.cwrap("pec_get_result", "number", ["number"]);
    draw();
  }).catch(function (e) {
    errorBox.hidden = false;
    errorBox.textContent = "Could not start the WebAssembly module: " + e;
    status.textContent = "";
  });
})();
