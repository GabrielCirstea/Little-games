var c;  //the canvas
var ctx,rect; // to draw on canvas
var timpul;
var tc;
var gs=10;  // graphics multiplier
var shots = new Array();
var asteroizi = new Array();
function setUp(){
  console.log("Se face setup-ul!");
  document.getElementById("canvas").addEventListener("click",clickPresed);
  score.docPoints = document.getElementById("score");
  //score.docCombo = document.getElementById("combo");
  c = document.getElementById("canvas");
  ctx = c.getContext("2d");
  rect = c.getBoundingClientRect();
  tc = c.width/gs;  // marimea mapei
  //startAnimation();
  initAsteroizi(10);
  clearInterval(timer);
  var timer = setInterval(game,1000/15);
}
function startAnimation(){
  let size = 10;
  ctx.fillStyle="white";
  var timer=setInterval(drawHere,20);
  function drawHere(){
    if(size == c.height)
      clearInterval(timer);
    ctx.fillRect(0,0,size,size);
    size++;
  }
}
var score={
  points: 0,
  clicks:0,
  //docPoints = dcument.getElementById("score")
  //docCombo = document.getElementById("combo")
  comboMulti: 1,
  combo: function(){
    // dupa o secunda fara boom se pierde comboul
    score+=1*this.comboMulti;
    this.comboMulti+=0.1;
    if(this.timer)
      clearTimeout(this.timer);
    var _this=this;
    this.timer = setTimeout(function(){_this.comboMulti = 1},1000);
  },
  inScore: function(){
    this.points+=1*this.comboMulti;
    this.combo();
  }
}
Player = {
  X : 0,
  Y : 0
}
class Shot{
  constructor(x,y){
    this.x = x;
    this.y = y;
    this.distance = 0;
    this.speed = 1;
  }
  draw(){
    ctx.fillStyle = "black";
    ctx.fillRect((this.x-this.distance)*gs,this.y*gs,gs,gs);  // merge la dstanga
    ctx.fillRect(this.x*gs,(this.y-this.distance)*gs,gs,gs);  // merge in sus
    ctx.fillRect((this.x+this.distance)*gs,this.y*gs,gs,gs);  // merge la dreapta
    ctx.fillRect(this.x*gs,(this.y+this.distance)*gs,gs,gs);  // merge in jos
  }
  move(){
    this.distance+=this.speed;
    if(this.distance > tc)
      this.speed = 0;
    this.draw();
  }
}
class Asteroid{
  // o sa plece dintr-o parte a ecranului
  // merge intr0o singura directie
  constructor(){
    this.speed = 0.5;
    this.gs = 15;
    this.rewind();
    this.reborn = null;
  }
  makeItDone(instant=false){
    this.done = true;
    if(this.reborn != undefined && this.reborn != null)
      return;
    if(instant)
      this.rewind();
    else{
      var _this = this;
      this.reborn = setTimeout(function(){_this.rewind();},500);
    }
  }
  move(){
    this.x+=this.vx;
    this.y+=this.vy;
    if(this.x < 0 || this.x > tc)
      this.makeItDone(true);
    if(this.y <0 || this.y >tc)
      this.makeItDone(true);
    this.chekcCollision();
    if(!this.done){
      this.draw();
    }
  }
  draw(){
    ctx.fillStyle = "red";
    ctx.fillRect(this.x*gs-this.gs,this.y*gs-this.gs,gs+this.gs,gs+this.gs)
  }
  chekcCollision(){
    if(this.done)
      return;
    let n = shots.length;
    let marja = this.gs/gs ;//Math.abs(this.gs-gs);
    for(let i=0;i<n;i++){
      if(Math.abs(this.x-shots[i].x)<marja){
        let dist = Math.abs(this.y - shots[i].y);
        if( Math.abs(dist-shots[i].distance)<marja){
          shot(this.x,this.y);
          score.points+=1;
          this.makeItDone();
        }
      }
      if(Math.abs(this.y-shots[i].y)<marja){
        let dist = Math.abs(this.x-shots[[i]].x);
        if(Math.abs(dist-shots[i].distance)<marja){
          shot(this.x,this.y);
          score.points+=1;
          this.makeItDone();
        }
      }
    }
  } // checkCollision
  rewind(){
    this.vx = 0;
    this.vy = 0;
    let wall = Math.floor(Math.random()*4);
    switch (wall) {
      case 0:{ // peretele de sus
          this.y = 0;
          this.x = Math.floor(Math.random()*tc);
          this.vy = this.speed;
      }break;
      case 1:{ // peretele din dreapta
        this.x = tc;
        this.y =  Math.floor(Math.random()*tc);
        this.vx = -this.speed;
      }break;
      case 2:{ // peretele de jos
        this.y = tc;
        this.x = Math.floor(Math.random()*tc);
        this.vy = -this.speed;
      }break;
      case 3:{ // peretele din stanga
        this.x = 0;
        this.y = Math.floor(Math.random()*tc);
        this.vx = this.speed;
      }break;
    }//switch

    this.done = false;  // if it's done is dead
    clearTimeout(this.reborn);
    this.reborn = null;
  }
} // calss
function shot(x,y){
  // lanseaza proiectilele
  shots.push(new Shot(x,y))
}
function moves(){
  //ctx.clearRect(0,0,c.width,c.height);
  ctx.fillStyle="white";
  ctx.fillRect(0,0,c.height,c.width);
  shots.forEach((shot) => {
    shot.move();
  });
  let n = shots.length;
  for(let i=0;i<n;i++){
    if(shots[i].speed == 0){
      shots.splice(i,1);
      n--;
    }
  }
  asteroizi.forEach((ast) => {
    ast.move();
  });
  return;
  n = asteroizi.length;
  for (var i = 0; i < n; i++) {
    if(asteroizi[i].done)
    asteroizi.splice(i,1);
    n--;
  }
}
function clickPresed(){
  Player.X = (event.clientX - rect.left)/gs;
  Player.Y = (event.clientY - rect.top)/gs;
  shot(Player.X,Player.Y);
  score.clicks++;
}
function game(){
  moves();
  score.docPoints.innerHTML=score.points;
  //score.docCombo.innerHTML=score.comboMulti;
}
function initAsteroizi(n){
  for (var i = 0; i < n; i++) {
    asteroizi.push(new Asteroid);
  }
}
