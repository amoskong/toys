// Create the canvas
var canvas = document.createElement("canvas");
var ctx = canvas.getContext("2d");
var mousePos;
var audio = new Audio('success.mp3');
var shot = false;
var count = 0

canvas.width = 1600;
canvas.height = 900;
document.body.appendChild(canvas);

// Background image
var bgReady = false;
var bgImage = new Image();
bgImage.onload = function () {
	bgReady = true;
};
bgImage.src = "images/background2.png";


// Monster image
var monsterReady = false;
var monsterImage = new Image();

monsterImage.onload = function () {
	monsterReady = true;
};
//monsterImage.src = "images/monster.png";
//monsterImage.src = "images/mascot_3.png";
monsterImage.src = "images/daemon-phk.png";

// Monster image
var monster2Ready = false;
var monster2Image = new Image();

monster2Image.onload = function () {
	monster2Ready = true;
};
//monsterImage.src = "images/monster.png";
monster2Image.src = "images/mascot_3.png";

// Hero image
var heroReady = false;
var heroImage = new Image();
heroImage.onload = function () {
	heroReady = true;
};
//heroImage.src = "images/hero.png";
heroImage.src = "images/target.png";

// Game objects
var hero = {
	speed: 256 * 1.3 // movement in pixels per second
};
var monster = {};
var monstersCaught = 0;

// Handle keyboard controls
var keysDown = {};
var mouseMove = {};
var Click = {};

addEventListener("keydown", function (e) {
	keysDown[e.keyCode] = true;
}, false);

function getMousePos(canvas, evt) {
        var rect = canvas.getBoundingClientRect();
        return {
          x: evt.clientX - rect.left,
          y: evt.clientY - rect.top
        };
}

addEventListener("mousemove", function (e) {
        mousePos = getMousePos(canvas, e);
	mouseMove[e.keyCode] = true;
}, false);

addEventListener("click", function (e) {
	Click[e.keyCode] = true;
	if ((hero.x + 100)    <= (monster.x + 50)
	     && (hero.x + 100) >= monster.x
	     && (hero.y + 100) <= (monster.y + 50)
	     && (hero.y + 100) >= monster.y) {
            shot = true;
        } else
            shot = false;
}, false);

addEventListener("keyup", function (e) {
	delete keysDown[e.keyCode];
}, false);

// Reset the game when the player catches a monster
var reset = function (first) {
        if (first) {
	    hero.x = canvas.width / 2 - 100;
	    hero.y = canvas.height / 2 - 100;
        } else {
	    hero.x = hero.x;
	    hero.y = hero.y;
        }

	// Throw the monster somewhere on the screen randomly
	monster.x = 32 + (Math.random() * (canvas.width - 64));
	monster.y = 32 + (Math.random() * (canvas.height - 64));
};

// Update game objects
var update = function (modifier) {
        count++;

	if (38 in keysDown) { // Player holding up
		hero.y -= hero.speed * modifier;
	}
	if (40 in keysDown) { // Player holding down
		hero.y += hero.speed * modifier;
	}
	if (37 in keysDown) { // Player holding left
		hero.x -= hero.speed * modifier;
	}
	if (39 in keysDown) { // Player holding right
		hero.x += hero.speed * modifier;
	}

       if ( mousePos && mouseMove) {
           hero.x = mousePos.x - 100;
           hero.y = mousePos.y - 100;
       }

	// Are they touching?
	if ( shot && Click &&
		(hero.x + 100)    <= (monster.x + 100)
		&& (hero.x + 100) >= monster.x
		&& (hero.y + 100) <= (monster.y + 100)
		&& (hero.y + 100) >= monster.y
	) {
		++monstersCaught;
                audio.play();
		reset();
                shot = false;
	} else if (count % 70 == 0) {
                
                //audio.play();
		reset();
                shot = false;
                count = 1;
        }
};

// Draw everything
var render = function () {
	if (bgReady) {
		ctx.drawImage(bgImage, 0, 0);
	}

	if (monsterReady) {
		ctx.drawImage(monsterImage, monster.x, monster.y);
        }

	//if (monster2Ready) {
	//	ctx.drawImage(monsterImage2, monster.x, monster.y);
	//}

	if (heroReady) {
		ctx.drawImage(heroImage, hero.x, hero.y);
	}

	// Score
	ctx.fillStyle = "rgb(250, 250, 250)";
	ctx.font = "24px Helvetica";
	ctx.textAlign = "left";
	ctx.textBaseline = "top";
	ctx.fillText("Goblins caught: " + monstersCaught, 32, 32);
};

// The main game loop
var main = function () {
	var now = Date.now();
	var delta = now - then;

	update(delta / 1000);
	render();

	then = now;

	// Request to do this again ASAP
	requestAnimationFrame(main);
};

// Cross-browser support for requestAnimationFrame
var w = window;
requestAnimationFrame = w.requestAnimationFrame || w.webkitRequestAnimationFrame || w.msRequestAnimationFrame || w.mozRequestAnimationFrame;

// Let's play this game!
var then = Date.now();
reset(true);
main();
