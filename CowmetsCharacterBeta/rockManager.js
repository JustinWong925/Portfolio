function rockManager(player,auto){
	this.player = player;
	this.auto = auto;
	this.maxSize = 10;
	this.pause = false;
	this.rockArr = new List();
	this.rockImg = new Array();
	this.rockImg.push(Textures.load("http://www.colorhexa.com/c0c0c0.png")); //smallAsteroid
	world.addChild(this);
}











rockManager.prototype.update = function(d){
	if(!this.pause){
		if(this.auto){
			this.autoGenerate();
		}
	}
};


rockManager.prototype.autoGenerate = function(){
	
	 while(this.rockArr.length<this.maxSize){
		var x = 10+Math.random()*(canvas.width-20);
		var y = -20 ;
		var angle = -90+Math.random()*180;
		var decideForMe =Math.random()*100;
		
		if(decideForMe<90){
	    	this.generateSR(x,y, angle, 1, 1,false);
	   	}else{
	   		this.generateBR(x,y, angle, 1, 1,false);
	   	}
	 } 
};




rockManager.prototype.setMax = function(num){
	this.maxSize=num;
};


rockManager.prototype.switchAuto = function(){
	this.auto = !this.auto;
	return this.auto;
};





rockManager.prototype.generateSR = function(x,y, angle, healthMult, speedMult,stag){
	this.rockArr.push(new smallRock(x,y, angle, healthMult, speedMult, 20,45, 45,this.player,stag,this));
};






rockManager.prototype.generateBR = function(x,y, angle, healthMult, speedMult, stag){
	
	this.rockArr.push(new bigRock(x,y, angle, healthMult, speedMult, 20,45, 45,this.player,stag,this));
};


rockManager.prototype.generateC = function(x,y, angle, healthMult, speedMult, mineRate,d,e,r){
	
	this.rockArr.push(new comet(x,y, angle, healthMult, speedMult, this.player, this,mineRate,d,e,r));
};









function comet(x,y, angle, healthMult, speedMult, player, manager,mineRate,d,e,r){
	this.manager=manager;
	this.player = player;
	this.onPlayer = false;
	this.speedMult = speedMult; //assume values 1<=speedMult; used to make them harder/easier for levels
	this.angle =angle;
	this.hO = new mineBar(mineRate,200,d,e,r);
	
	
	Sprite.call(this);
    this.width = 50;  //we can make them bigger or smaller, the actual size will be debated once we work on art
    this.height = 50;
 	this.image = Textures.load("http://www.colorhexa.com/c000c0.png" );

	this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
    this.initi = false;
    this.lifeTime = 0; //used to show how long an object has been alive, and used so that after certain intervals activate something, 
    				//ie, if(this.lifetime % "interval of time"  == 0){ doSOmething} 
    this.health = 100*healthMult; //assume values 0.1<=healthMult<=5; used to make them harder/easier for levels
 	world.addChild(this);
};
comet.prototype = new Sprite();




comet.prototype.update = function(d){
	if(!this.manager.pause){
		
		
		if(!this.onPlayer){
			if(check2Ob(this,this.player)){
				this.onPlayer = true;
			}
		}
		
		
		
		if(!this.onPlayer){
			this.move();
			if(check2Ob(this,this.player)){
				this.onPlayer = true;
			}
		}else{
			this.mine();
		}
		
	
		this.lifeTime++;
	}
};




comet.prototype.move= function(){
	if(check2Ob(this,this.player)){
		this.onPlayer=true;
		this.player.onComet = true;
		this.player.comet=this;
	}
	
	
	
	
	this.x += 2*this.speedMult*Math.sin(DTR(this.angle));
	this.y += 2*this.speedMult*Math.cos(DTR(this.angle));
	
	if(checkPOBn(this)){
		this.manager.rockArr.remove(this);
		world.removeChild(this);
	}
	
	if(check2Ob(this,this.player)){
		this.onPlayer=true;
		this.player.onComet = true;
		this.player.comet=this;
	}
	//this.angle+= 0.1;   
};



comet.prototype.mine = function(){
	if(!this.initi){
		this.hO.init();
		this.initi = true;
	}
};








 comet.prototype.giveResource = function(){
 	
 	
 	
 	
 	
 };







function mineBar(mineRate,max,d,e,r){
	if(e+d+r!= 1){
		console.log("incorrect usage of d,e,r, must be values 0<=n<=1 & sum=1");
		return false;
	}
	this.mineRate = mineRate;
	this.progress = 0;
	this.max = max;
	this.d = d;
	this.e = e;
	this.r = r;
	this.lifeTime = 0;
	this.health = 100;
	
	this.D = new mineBarD(max,d,e,r);
	this.E = new mineBarE(max,d,e,r);
	this.R = new mineBarD(max,d,e,r);
	this.C = new mineBarC(max);
	
}

mineBar.prototype.init = function(){
	world.addChild(this);
	//this.D.init();
	//this.E.init();
	this.R.init();
	//this.C.init();
};


mineBar.prototype.update = function(d){
	console.log(this.mine());
	console.log(this.adjust());
};


mineBar.prototype.mine =  function(){
		if(this.progress==100){
			return true;
		}else{
			if(this.lifeTime%this.mineRate ==0){
				this.progress++;
				this.C.y++;
				this.C.width++;
			}
		}
		this.lifeTime++;
		return false;
};

mineBar.prototype.adjust = function(){
		if(this.health==0){
			return true;
		}
		if(this.health<50){
			this.D.width= this.max*this.d +   this.max*this.e*   ((50-this.health)/50 )         ;
		}
		return false;
};













function mineBarD(max,d,e,r){
	Sprite.call(this);
	this.width = max*d;
	this.height = 20;
	//this.xoffset = -this.width;
	this.yoffset = -this.height;
	this.x = 20;
	this.y = canvas.height-10;
	
	this.image = Textures.load("http://www.colorhexa.com/ff0000.png");
	
}
mineBarD.prototype = new Sprite();
mineBarD.prototype.init = function(){
	world.addChild(this);
};







function mineBarE(max,d,e,r){
	Sprite.call(this);
	this.width = max*e;
	this.height = 20;
	//this.xoffset = -this.width;
	this.yoffset = -this.height;
	this.x = 20+max*d;
	this.y = canvas.height-10;
	
	this.image = Textures.load("http://www.colorhexa.com/f7ff00.png");
	
	
}
mineBarE.prototype = new Sprite();
mineBarE.prototype.init = function(){
	world.addChild(this);
};




function mineBarR(max,d,e,r){
	Sprite.call(this);
	this.width = max*r;
	this.height = 20;
	//this.xoffset = -this.width;
	this.yoffset = -this.height;
	this.x = 20+max*d+max*e;
	this.y = canvas.height-10;
	
	this.image = Textures.load("http://www.colorhexa.com/00e390.png");
	
	
}
mineBarR.prototype = new Sprite();
mineBarR.prototype.init = function(){
	world.addChild(this);
};







function mineBarC(max){
	Sprite.call(this);
	this.width = max;
	this.height = 10;
	//this.xoffset = -this.width;
	this.yoffset = -this.height;
	this.x = 20;
	this.y = canvas.height-10;
	
	this.image = Textures.load("http://www.colorhexa.com/0392a3.png");
}
mineBarC.prototype = new Sprite();
mineBarR.prototype.init = function(){
	world.addChild(this);
};




















healthBar.prototype.mineColor = function(){
	
	var stringBase = "http://www.colorhexa.com/";
	var cH = "ff";
	var yH = "00";
	var mH = "00.png";
	var x = Math.floor((this.health)*511/this.maxH);

	if(x==0){}
	else if(x<256){
		var yH = x.toString(16); 
		if(yH.length==1){
			yH = "0"+yH;
		}

	}else  if(x<511){
		yH = "ff";
		x -=256;
		var t = 256-x;
   		var cH = t.toString(16);
		if(cH.length==1){
			cH = "0"+cH;
		}
   		
	}else if(x==511){
		cH= "00";
		yH = "ff";
	}
	
	var neString = stringBase+cH+yH+mH;
	return neString;
};





























function smallRock(x,y, angle, healthMult, speedMult, cellSize,numCelli, numCellj,player, stag,manager){
	this.manager=manager;
	this.worm = null;
	this.player = player;
	this.stag = stag;
	Sprite.call(this);
	this.speedMult = speedMult; //assume values 1<=speedMult; used to make them harder/easier for levels
    this.width = 50;  //we can make them bigger or smaller, the actual size will be debated once we work on art
    this.height = 50;
    
    

 	this.image = Textures.load("http://www.colorhexa.com/c0c0c0.png" );
 	
 	this.cell_size = cellSize; //used later in grid checks, just leave here for now
 	this.maxI = numCelli;
	this.maxJ = numCellj;
	this.angle =angle;
 	
	this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
    
    this.lifeTime; //used to show how long an object has been alive, and used so that after certain intervals activate something, 
    				//ie, if(this.lifetime % "interval of time"  == 0){ doSOmething} 
    this.health = 100*healthMult; //assume values 0.1<=healthMult<=5; used to make them harder/easier for levels
 	world.addChild(this);
};
smallRock.prototype = new Sprite();




//for the moment, we will be using the smallRock's update function to show proof of concept,
//so in here, you will call your move functions, call your out of bounds check
//and your shoot methods
//we will worry about implementing a "delete" later
smallRock.prototype.update = function(d){
	if(!this.manager.pause){
		if(!this.stag){
			this.move();
		}else{
		
		}
	
		this.lifeTime++;
	}
};



//let this function control how it should move, not if its going to be out of bounds
smallRock.prototype.move= function(){
	
	this.x += 2*this.speedMult*Math.sin(DTR(this.angle));
	this.y += 2*this.speedMult*Math.cos(DTR(this.angle));
	
	if(checkPOBn(this)){
		this.manager.rockArr.remove(this);
		world.removeChild(this);
		
		//this.x = Math.random()*canvas.width;
		//this.y = 0; 
	}
	
	if(check2Ob(this,this.player)){
		this.manager.rockArr.remove(this);
		world.removeChild(this);
		this.player.h.       setH      (this.player.h.health-10);
	}
	//this.angle+= 0.1;   
};






































//////////////////////////////////////////////////////
//////////////BIG ROCK////////////////////////////////////////
//////////////////////////////////////////////////////


function bigRock(x,y, angle, healthMult, speedMult, cellSize,numCelli, numCellj,player,stag,manager){
	this.manager=manager;
	this.player = player;
	this.stag = stag;
	Sprite.call(this);
	this.speedMult = speedMult; //assume values 1<=speedMult; used to make them harder/easier for levels
    this.width = 200;  //we can make them bigger or smaller, the actual size will be debated once we work on art
    this.height = 200;
    
    

 	this.image = Textures.load("http://www.colorhexa.com/c0c0c0.png" );	
 	
 	this.cell_size = cellSize; //used later in grid checks, just leave here for now
 	this.maxI = numCelli;
	this.maxJ = numCellj;
	this.angle =angle;
 	
	this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;

    this.lifeTime = 0; //used to show how long an object has been alive, and used so that after certain intervals activate something, 
    				//ie, if(this.lifetime % "interval of time"  == 0){ doSOmething} 
    this.health = 100*healthMult; //assume values 0.1<=healthMult<=5; used to make them harder/easier for levels
 	world.addChild(this);
};
bigRock.prototype = new Sprite();







bigRock.prototype.move= function(){
	if(!this.stag){
		
		
		
		this.x += .5*this.speedMult*Math.sin(DTR(this.angle));
		this.y += .5*this.speedMult*Math.cos(DTR(this.angle));
		
		if(this.x > canvas.width || this.y > canvas.height ){
			world.removeChild(this);
			/*
			this.x = Math.random()*canvas.width;
			this.y = 0; 
			*/
		}
		
		
		
		
	}
	
	//this.angle+= 0.1;   
};





bigRock.prototype.update = function(d){
	
	if(!this.manager.pause){
		if(this.lifeTime>=400){
			
			this.explosion();
			
		}
		this.move();
		this.lifeTime++;
	}
};

bigRock.prototype.explosion = function(){
	
	var t = Math.floor(Math.random()*4 +2);
	for( var j = 0; j < t ; ++j){
		//new x and y must start at the new location 
		var angle = Math.random()*360;
		var xMod = Math.sin(DTR(angle))*this.width/2;
		var yMod = Math.cos(DTR(angle))*this.height/2;
		this.manager.generateSR(this.x+xMod,this.y+yMod, angle, 0.5, 1,false);

	}
	console.log("here with " + this.manager.rockArr.remove(this));
	world.removeChild(this);
};









function worm(x,y, healthMult, speedMult, cellSize,numCelli, numCellj, player, manager,rock){
	Sprite.call(this);
	this.rock = rock;
	
	
	this.manager = manager;
	this.speedMult = speedMult; //assume values 1<=speedMult; used to make them harder/easier for levels
    this.width = 30;  //we can make them bigger or smaller, the actual size will be debated once we work on art
    this.height = 30;

 	this.image = Textures.load("http://www.colorhexa.com/c0c0c0.png" );
 	

    this.player = player;
    

 	this.follow = false;
 	this.followdist = dist;
 	
 	this.cell_size = cellSize; //used later in grid checks, just leave here for now
 	this.maxI = numCelli;
	this.maxJ = numCellj;

 	
	this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
    
    this.lifeTime=0; //used to show how long an object has been alive, and used so that after certain intervals activate something, 
    				//ie, if(this.lifetime % "interval of time"  == 0){ doSOmething} 
    this.health = 100*healthMult; //assume values 0.1<=healthMult<=5; used to make them harder/easier for levels
 	world.addChild(this);
	
}


worm.prototype.shoot = function(){
	var oposite = this.x-this.player.x;
	var adjacent = this.y-this.player.y;
	
	var hypotenuse = Math.sqrt(  yDist*yDist +  xDist*xDist );
	
	var angle = Math.asin(oposite/hypotenuse);
	
	this.angle+=angle;

};







function wAmmo(x,y,angle){
	

	
	
	this.switchDir = false;
	this.defaultAngle = angle;
	
	Sprite.call(this);

    this.width = 17.5/3;
    this.height = 22.5/3;
    
    this.angle = angle;
    
    this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
    

    this.image = Textures.load("http://www.colorhexa.com/00ffff.png");
    
    world.addChild(this);
};

wAmmo.prototype = new Sprite();

 

wAmmo.prototype.update = function(d){
	
		var xVel=2;
		var yVel=8;
		
		if(this.switchDir){
			xVel=8;
			yVel=2;
		}

		this.x += xVel*Math.sin(DTR(this.defaultAngle));
		this.y -= yVel*Math.cos(DTR(this.defaultAngle));
		
		
		
		
		
		//if(checkPOBn){
		//	world.removeChild(this);
		///}
};
	