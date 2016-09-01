function alienManager(player,auto){
	this.pause = false;
	this.player = player;
	this.auto = auto;
	this.maxSize = 10;
	this.alienArr = new List();
	world.addChild(this);
}



alienManager.prototype.update = function(d){
	if(this.auto){
		this.autoGenerate();
	}
};
















alienManager.prototype.autoGenerate = function(){
	 while(this.alienArr.length<this.maxSize){
		var x = 10+Math.random()*(canvas.width-20);
		var y = -20 ;
		
		
		var decideForMe =Math.random()*100;
		if(decideForMe<90){
			var follow = Math.random()*canvas.width/2;
			this.createF( x,y,follow);
	   	}else{
	   		this.createS(x,y,null,1);
	   	}
	 }
};


alienManager.prototype.createF = function(x,y,dist){
	this.alienArr.push(new alien(x,y, 2, 2, 20,45, 45, this.player,this,dist));
};


alienManager.prototype.createS = function(x,y,path,pathSpeed){
	this.alienArr.push(new spammer(x,y,1, 1, 20, 45, 45,path,pathSpeed,this));
};













function alien(x,y, healthMult, speedMult, cellSize,numCelli, numCellj, player, manager,dist){
	
	this.manager = manager;
	Sprite.call(this);
	this.speedMult = speedMult; //assume values 1<=speedMult; used to make them harder/easier for levels
    this.width = 30;  //we can make them bigger or smaller, the actual size will be debated once we work on art
    this.height = 30;

 	this.image = Textures.load("http://www.colorhexa.com/2b00ff.png" );
 	

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
    this.jesusRoom = 20;
    
    this.lifeTime=0; //used to show how long an object has been alive, and used so that after certain intervals activate something, 
    				//ie, if(this.lifetime % "interval of time"  == 0){ doSOmething} 
    this.health = 100*healthMult; //assume values 0.1<=healthMult<=5; used to make them harder/easier for levels
 	world.addChild(this);
};


alien.prototype = new Sprite();




//for the moment, we will be using the alien's update function to show proof of concept,
//so in here, you will call your move functions, call your out of bounds check
//and your shoot methods
//we will worry about implementing a "delete" later
alien.prototype.update = function(d){
	if(!this.manager.pause){
		this.move();
		if(this.lifeTime%30 ==0){
			//console.log("shooting");
			this.shoot();
		}
		this.lifeTime++;
	}
};


//let this function control how it should move, not if its going to be out of bounds
//moves down if not within 40 units of it
alien.prototype.move= function(){
	var speed = 2;
	
	
	if(       (this.x-17.5/6    >          this.player.x-this.player.width/2)     &&   (this.x+17.5/6<this.player.x+this.player.width/2)){
		//console.log("in sweetspot");
	}else{
	
	
		if(this.x-17.5/6    <          this.player.x-this.player.width/2) {

			this.x+= speed;
		}else if(this.x+17.5/6  >  this.player.x+this.player.width/2){

			this.x-= speed;
		}
	}
	
	
	
	
	
	
	if(this.y+this.height/2+this.followdist+this.jesusRoom>= this.player.y-this.player.height/2){
		this.follow = true;
	}
	
	
	
	
	
	if(!this.follow){
		var dist = (this.player.y-this.player.height/2)-(this.y+this.jesusRoom+this.followdist+this.height/2);
			
		if(dist<speed){
			speed=dist;
			this.follow=true;
		}
		this.y+= speed;

	}else{
		this.y=this.player.y-this.player.height/2-this.followdist-this.jesusRoom-this.width/2;
	}
};







//will implement some way of shooting the ammo
alien.prototype.shoot = function(){
	//console.log("shooting");
	var tempS = new fAmmo(this.x, this.y + this.height/2,this.player);
};




alien.prototype.deleteThis = function(){
	this.manager.alienArr.remove(this);
	world.removeChild(this);
};









//these are similar to the ammo objects im using for the player at the moment and you can use them for now as proof of concept that your object shoots
function fAmmo(x,y,player){
	this.player = player;
	this.angle = 0;//dont worry about this for now yasha, this will be incoporated later
	Sprite.call(this);

    this.width = 17.5/3;
    this.height = 22.5/3;
    
    this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
    
    this.image = Textures.load("http://www.colorhexa.com/0f8921.png");
    
    world.addChild(this);
};

fAmmo.prototype = new Sprite();


fAmmo.prototype.update = function(d){
	if(!this.player.pause){
		if(check2Ob(this,this.player)){
			
			this.player.h.setH(this.player.h.health-1);
			world.removeChild(this);
		}
		if(checkPOBn(this,this.player)){
			
			world.removeChild(this);
		}
		
		
		
		
		
		this.y += 5; //moves downward at a certain speed 
		
		
		
		if(check2Ob(this,this.player)){
			
			this.player.h.setH(this.player.h.health-1);
			world.removeChild(this);
		}
		if(checkPOBn(this,this.player)){
			
			world.removeChild(this);
		}
	}
};












/////////////////////// SPAMMER ///////////////////
///////////////////////////////////////////////////


function spammer(x,y, healthMult, speedMult, cellSize, numCelli, numCellj,path,pathSpeed,manager)
{
	this.manager = manager;
	Sprite.call(this);
	this.angle = 0;
	this.path = path;
	this.currI = 0;
	this.pS = pathSpeed;
	this.speedMult = speedMult; //assume values 1<=speedMult; used to make them harder/easier for levels
    this.width = 30;  //we can make them bigger or smaller, the actual size will be debated once we work on art
    this.height = 30;

 	this.image = Textures.load("http://www.colorhexa.com/3f6616.png");
 	
 	this.cell_size = cellSize; //used later in grid checks, just leave here for now
 	this.maxI = numCelli;
	this.maxJ = numCellj;

 	
	this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x + 15;
    this.y = y + 15;
    
    this.lifeTime = 0; //used to show how long an object has been alive, and used so that after certain intervals activate something, 
    				//ie, if(this.lifetime % "interval of time"  == 0){ doSOmething} 
    this.health = 100 * healthMult; //assume values 0.1<=healthMult<=5; used to make them harder/easier for levels
 	world.addChild(this);
};
spammer.prototype = new Sprite();




//for the moment, we will be using the spammer's update function to show proof of concept,
//so in here, you will call your move functions, call your out of bounds check
//and your shoot methods
//we will worry about implementing a "delete" later
spammer.prototype.update = function(d){
	if(!this.manager.pause){
		this.move();
		if(this.OOB())
		{
			world.removeChild(this);
		}
		//this.willHit(); // check to see if spammer collided with Madcow
		this.shoot();
		this.lifeTime++;
	}
};






//let this function control how it should move, not if its going to be out of bounds
spammer.prototype.move = function()
{
	
		
		
		
		
		this.x += 3*this.speedMult*Math.sin(DTR(this.angle));
		this.y += 3*this.speedMult*Math.cos(DTR(this.angle));
	
	     
	    
		//this.y += 3;
};





//will simulate as if it had moved (does NOT CHANGE any fields of an objects, but can have temp vars and manipulate those) 
//and return true if it will be out of bounds or false if will not
spammer.prototype.OOB = function()
{
	var minY = this.y - this.height/2;
	var maxX = this.x + this.height/2;
	
	if(minY > canvas.height || maxX > canvas.width)
	{
		//console.log("spammer is out of bounds.");
		return true;
	}
	return false;
};







//similar to OOB, except assume the spammer already moved and this will compare against an object,
//and assume that the object has an x,y,width,height field
spammer.prototype.willHit = function(object)
{
	var minX1 = this.x - this.width/2;
	var maxX1 = this.x + this.width/2;
	var minY1 = this.y - this.height/2;
	var maxY1 = this.y + this.height/2;
	
	var minX2 = Object.x - Object.width/2;
	var maxX2 = Object.x + Object.width/2;
	var minY2 = Object.y - Object.height/2;
	var maxY2 = Object.y + Object.height/2;
	
	if(minX2 < maxX1 && minY2 < maxY1 && maxX2 > minX1 && maxY2 > minY1)
	{
		//console.log("collided");
		return true;
	}
	return false;
};









//will implement some way of shooting the ammo
spammer.prototype.shoot = function()
{
	if(this.lifetime % 0 == 0)
	{
		var temp_ammo = new spAmmo(this.x + this.width / 2, this.y);
	}
};


spammer.prototype.respawn = function()
{
	if(this.i != Math.floor (this.maxI/2)  )
	{
		this.i = Math.floor (this.maxI/2);
	}else
	{
		this.i = 1;
	}
	
	
	if(this.j != Math.floor (this.maxJ/2)  )
	{
		this.j = Math.floor (this.maxJ/2);
	}else
	{
		this.j = 1;
	}

	this.x = this.cell_size / 2 + this.i * this.cell_size;
	this.y = this.cell_size / 2 + this.j * this.cell_size;
};











//implement something that will attempt respawn to the specified x and y 
//location, but will only allow the x (considering object width) locations to be >0 and <canvas width
//and a y location at least 50 "y values" above (negative) above the player
//if the x condition fails, just choose random x location in bounds, if y fails,
//choose top of screen (y=0)
spammer.prototype.respawnTo = function(x, y)
{
	this.x = x;
	this.y = y;
};












//these are similar to the ammo objects im using for the player at the moment and you can use them for now as proof of concept that your object shoots
function spAmmo(x,y){
	
	this.angle = 0;//dont worry about this for now yasha, this will be incoporated later
	Sprite.call(this);

    this.width = 17.5/3;
    this.height = 22.5/3;
    
    this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
    
    this.image = Textures.load("http://www.colorhexa.com/0f8921.png");
    
    world.addChild(this);
};

spAmmo.prototype = new Sprite();


spAmmo.prototype.update = function(d){
	if(!this.player.pause){
		if(check2Ob(this,this.player)){
				
				this.player.h.setH(this.player.h.health-1);
				world.removeChild(this);
			}
			if(checkPOBn(this,this.player)){
				
				world.removeChild(this);
			}
			
			
			
			
			
			this.y += 5; //moves downward at a certain speed 
			
			
			
			if(check2Ob(this,this.player)){
				
				this.player.h.setH(this.player.h.health-1);
				world.removeChild(this);
			}
			if(checkPOBn(this,this.player)){
				
				world.removeChild(this);
			}
	}
};
	

	

