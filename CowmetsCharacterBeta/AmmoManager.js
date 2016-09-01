function AmmoMNGR(cellSize,numCelli,numCellj){
	this.collList = new List();
	this.pause = false;
	
	
	
	this.cell_size = cellSize;
	this.maxJ = numCellj;
	this.maxI = numCelli;
	
	this.occMap = new Array(numCelli);
	
	for(var i = 0; i<numCelli; i++){
		this.occMap[i] = new Array(numCellj);
		for(var j = 0; j<numCelli; j++){
			this.occMap[i][j] = false;
		}
	}
	
	

	

	
	this.ammoArr = new List();

}


AmmoMNGR.prototype.getAmmo = function(type,level,x,y){
	
	
	switch(type){
		
		case "ammo":
			switch(level){
				case 0:
					var temp = new mcAmmo(x,y,0,false,this);
					break;
					
				case 1:
					var temp0 = new mcAmmo(x+5,y,0,false,this);
					var temp1 = new mcAmmo(x-5,y,0,false,this);
					break;
				case 2:
					var temp0 = new mcAmmo(x+10,y,0,false,this);
					var temp1 = new mcAmmo(x,y,0,false,this);
					var temp2 = new mcAmmo(x-10,y,0,false,this);
					break;
					
					
					
					
				case 3:
					var temp0 = new mcAmmo(x-10,y,-15,false,this);
					var temp1 = new mcAmmo(x,y,0,false,this);
					var temp2 = new mcAmmo(x+10,y,+15,false,this);
					break;
				case 4:
					var temp0 = new mcAmmo(x+15,y,0,false,this);
					var temp1 = new mcAmmo(x+5,y,0,false,this);
					var temp2 = new mcAmmo(x-5,y,0,false,this);
					var temp3 = new mcAmmo(x-15,y,0,false,this);
					break;
				default:
					var temp = new mcAmmo(x,y,0,false,this);
					break;
				
			}
		
			break;
			
			
			
			
		case "missle":
			
			switch(level){
				case 0:
					var temp = new mcMissle(x,y,this);
					break;
					
				case 1:
					var temp0 = new mcMissle(x+5,y,this);
					var temp1 = new mcMissle(x-5,y,this);
					break;
				case 2:
					var temp0 = new mcMissle(x+10,y,this);
					var temp1 = new mcMissle(x,y,this);
					var temp2 = new mcMissle(x-10,y,this);
					break;
					
				default:
					var temp = new mcMissle(x,y,this);
					break;
				
			}
			break;
		case "laser":
			switch(level){
				case 0:
					var temp = new mcLaser(x,y,this);
					break;
				case 1:
					var temp = new mcLaser(x-10,y,this);
					var temp = new mcLaser(x+10,y,this);
					break;
				case 2:
					var temp = new mcLaser(x-10,y,this);
					var temp = new mcLaser(x,y,this);
					var temp = new mcLaser(x+10,y,this);
					
					break;
				default:
					var temp = new mcLaser(x,y,this);
					break;
			}
			break;
			
		case "grenade":
	
			
			
			
			switch(level){
				case 0:
					var temp = new mcGrenade(x,y,0,0,1,this);
					break;
				case 1:
					var temp = new mcGrenade(x+5,y,30,0,1,this);
					var temp2 = new mcGrenade(x-5,y,-30,0,1,this);
					break;
				case 2:
					var temp = new mcGrenade(x+5,y,30,45,0.9,this);
					var temp2 = new mcGrenade(x-5,y,-30,45,1.5,this);
					
					break;
				default:
					var temp = new mcGrenade(x+15,y,45,45,0.5,this);
					var temp2 = new mcGrenade(x-25,y,-45,45,1,this);
					var temp1 = new mcGrenade(x,y,0,0,1.5,this);
					var temp3 = new mcGrenade(x+5,y,15,0,1,this);
					var temp4 = new mcGrenade(x-5,y,-15,0,0.5,this);
					break;
			}
			break;
		default:
			var temp = new mcAmmo(x,y,0,false,this);
			break;
	}
	
	
	
	
};
























function mcGrenade(x,y,angle,modAngle,upgrade,manager){
	this.manager= manager;
	this.lifeTime= 0;
	this.defaultAngle = angle;
	this.mdA = modAngle;
	this.upgrade = upgrade;
	Sprite.call(this);

    this.width = 17.5/1.5;
    this.height = 22.5/1.5;
    
    this.angle = angle;
    
    this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
    this.fuse = 70;
  
    
    this.image = Textures.load("http://www.colorhexa.com/ffff00.png");
    
    world.addChild(this);
};

mcGrenade.prototype = new Sprite();



/*

mcGrenade.prototype.dummyUpdate = function(){
		   
		//console.log(Math.sin(DTR(this.defaultAngle)));
		this.x += 2*Math.sin(DTR(this.defaultAngle));
		this.y -= 4*Math.cos(DTR(this.defaultAngle));
		console.log("grenade ALive");
		
		if(this.lifeTime > this.fuse){
			world.removeChild(this);
			console.log("grenade died");
			var temp0 = new  mcAmmo(this.x,this.y,0+this.mdA,false);
			var temp1 = new  mcAmmo(this.x,this.y,90+this.mdA,true);
			var temp2 = new  mcAmmo(this.x,this.y,180+this.mdA,false);
			var temp2 = new  mcAmmo(this.x,this.y,270+this.mdA,true);
			
		}
		
		this.lifeTime++;
		if(this.x<0 || this.x>canvas.width || this.y<0 || this.y>canvas.width){
			world.removeChild(this);
		}
		
};

*/

mcGrenade.prototype.update = function(d){
	   
		//console.log(Math.sin(DTR(this.defaultAngle)));
		this.x += 2*Math.sin(DTR(this.defaultAngle));
		this.y -= 4*Math.cos(DTR(this.defaultAngle));
		console.log("grenade ALive");
		
		if(this.lifeTime > this.fuse){
			world.removeChild(this);
			console.log("grenade died");
			var temp0 = new  mcAmmo(this.x,this.y,0+this.mdA,false);
			var temp1 = new  mcAmmo(this.x,this.y,90+this.mdA,true);
			var temp2 = new  mcAmmo(this.x,this.y,180+this.mdA,false);
			var temp2 = new  mcAmmo(this.x,this.y,270+this.mdA,true);
			
		}
		

		this.lifeTime += this.upgrade*1;
		if(this.x<0 || this.x>canvas.width || this.y<0 || this.y>canvas.width){
			world.removeChild(this);
		}
		
		//checkPOB(this,true);
};



function mcAmmo(x,y,angle,sD,dependant,manager){
	
	this.manager = manager;
	this.dependand=dependant;
	
	
	this.switchDir = sD;
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

mcAmmo.prototype = new Sprite();

 

mcAmmo.prototype.update = function(d){
	
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






function mcLaser(x,y,manager){
	this.manager = manager;
	this.increment= Math.floor(y/5);
	console.log(this.increment);
	this.lifeTime = 0;
	
	Sprite.call(this);

    this.width = 3;
    this.height = y/2;
    

    
    this.xoffset = -this.width/2;
	this.yoffset = -this.height;
    this.x = x;
    this.y = y;
    
  
    
    this.image = Textures.load("http://www.colorhexa.com/00ff00.png");
    
    world.addChild(this);
};
mcLaser.prototype = new Sprite();

mcLaser.prototype.update = function(d){
	this.y -= 20;
	
	//if(checkPOBn(this)){
	//	world.removeChild(this);
	//}
	this.lifeTime++;
		//console.log(Math.sin(DTR(this.defaultAngle)));
		//this.x += 2*Math.sin(DTR(this.defaultAngle));
		//this.y -= 6*Math.cos(DTR(this.defaultAngle));
		//checkPOB(this,true);
};






function mcMissle(x,y,manager){
	this.manager = manager;
	this.lifetime =0;
	this.vel = 2;
	Sprite.call(this);

    this.width = 17.5/2;
    this.height = 22.5/2;
    
    this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
    
    this.image = Textures.load("http://www.colorhexa.com/ff0000.png");
    
    world.addChild(this);
};

mcMissle.prototype = new Sprite();


mcMissle.prototype.update = function(d){
		checkPOB(this,true);
		if(this.lifetime >=70){
			this.vel = 8;
		}
		
		
		
		this.y -=this.vel;
		//if(checkPOBn(this)){
		//	world.removeChild(this);
		//}
		this.lifetime++;
		
		
};