import { getString, getFunction } from './index.js';
import { win } from './win/index.js';

const state = { running: false }

export function print(ptr) {
  console.log(getString(ptr));
}

export function getRandom() {
  return Math.random();
}

export function init() { }

let lastUpdate = Date.now();
const gameLoop = (loop, onComplete, time = 0) => {
  if (state.running) {
    requestAnimationFrame(() => gameLoop(loop, onComplete, time));
    let now = Date.now();
    let dt = now - lastUpdate;
    lastUpdate = now;
    loop(dt);
  } else {
    onComplete();
  }
}

export function runGameLoop(gameLoopPtr, onQuitPtr) {
  state.running = true;
  state.onQuit = getFunction(onQuitPtr);
  gameLoop(getFunction(gameLoopPtr));

}

export function createWindow(ptr, width, height) {
  document.title = getString(ptr);
  state.canvas = document.createElement('canvas');
  state.canvas.width = width;
  state.canvas.height = height;
  state.ctx = state.canvas.getContext('2d');
  state.win = win.createWindow(getString(ptr), width, height);
  state.win.element.appendChild(state.canvas);
  state.win.onClose = () => {
    state.running = false;
    state.onQuit();
  };
  state.win.onMinimize = () => {
    console.log('minimize');
  };
  state.win.onResize = (width, height) => {
    state.canvas.width = width;
    state.canvas.height = height;
  };
}

export function setDrawColor(r, g, b, a) {
  state.ctx.fillStyle = `rgba(${r}, ${g}, ${b}, ${a})`;
  state.ctx.strokeStyle = `rgba(${r}, ${g}, ${b}, ${a})`;
}

export function clearScreen() {
  state.ctx.fillRect(0, 0, state.canvas.width, state.canvas.height);
}

export function drawRect(x, y, width, height) {
  state.ctx.strokeRect(x, y, width, height);
}

export function fillRect(x, y, width, height) {
  state.ctx.fillRect(x, y, width, height);
}

export function drawCircle(x, y, radius) {
  state.ctx.beginPath();
  state.ctx.arc(x, y, radius, 0, 2 * Math.PI);
  state.ctx.stroke();
}

export function fillCircle(x, y, radius) {
  state.ctx.beginPath();
  state.ctx.arc(x, y, radius, 0, 2 * Math.PI);
  state.ctx.fill();
}

export function destroyWindow() {
  state.canvas.remove();
}

export function quit() {
  console.log('quit');
  state.running = false;
}

window.quit = quit;

export function setOnClick(onClickPtr) {
  state.canvas.addEventListener('click', e => {
    let rect = state.canvas.getBoundingClientRect();
    let x = e.clientX - rect.left;
    let y = e.clientY - rect.top;
    getFunction(onClickPtr)(x, y);
  });
}
