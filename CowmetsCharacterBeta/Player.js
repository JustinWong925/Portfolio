



function MadCow(x,y,upgrades,defaultWeapon,defaultLevel,burst){
	Sprite.call(this);
	this.width = 35;
    this.height = 45;
    this.xoffset = -this.width/2;
	this.yoffset = -this.height/2;
    this.x = x;
    this.y = y;
	
	
	
	this.currUpgrades = upgrades;//will possibly be array with values representing upgrades or an object with boolean checks, once more upgrades are discussed this will be implemented
	this.shootingSpeedUpgrade = 1;
	this.speedMult = 1;
	this.onComet = false;
	this.burst = burst;

    this.weaponConfig = new wepPair(defaultWeapon,defaultLevel); //base upgradeable field of madcow
    this.speedMult = 1;

 	this.image = Textures.load("http://www.colorhexa.com/ffffff.png");
 		
	this.comet = null;
    
    this.lifeTime = 0;
    this.setROF();
    
    this.aMNGR = new AmmoMNGR(20,45,45);
    this.h = new healthBar(100,0);
    world.addChild(this);
}


MadCow.prototype = new Sprite();
MadCow.prototype.shooting = false;
MadCow.prototype.shootTime =0;



MadCow.prototype.pauseP = function(){
	this.pause = !this.pause;
	this.aMNGR.pause = this.pause;
};

MadCow.prototype.setROF = function(){
	
	switch (this.weaponConfig.type){
		case "ammo":
			this.shootRate= 30;
			break;
		case "laser":
			this.shootRate = 90;
			break;
		case "missle":
			this.shootRate = 70;
			break;
		case "grenade":
			this.shootRate = 120;
			break;
		default:
			this.shootRate = 30;
			break;
	}

};




MadCow.prototype.update = function(d){
		
		if(!this.pause){			
		//Define a speed to move at
				var speed =1;
			
				
				
				
				
				if(this.comet ==null){
		
					if((gInput.down)&&(gInput.up)){}
					else if(gInput.down){
						this.y += 4.5-speed*1.25;
					}else 
					if(gInput.up){
						this.y -= 3 +2*speed;
					}
				}				
				
				
				
				
				
				
				
				if((gInput.left)  && (gInput.right)  ){}
				else if(gInput.left){
					this.x -= 4-speed;
					if(this.comet !=null){
						this.comet.x -= 4-speed;
					}
				}
				else if(gInput.right){
					this.x += 4-speed;
					if(this.comet !=null){
						this.comet.x += 4-speed;
					}
				}
				


				
				
				
				if(!this.shooting){
					if(gInput.space){
						this.shooting = true;
					}
					
    			}
    			
    			
    			if(this.shooting){
    				if(this.shootTime==0){
    					 this.aMNGR.getAmmo(this.weaponConfig.type ,this.weaponConfig.level,this.x,this.y-this.height/2);

    				}
    				
    				if(this.burst){
    					if(this.shootTime-5 ==0){
    					 this.aMNGR.getAmmo(this.weaponConfig.type ,this.weaponConfig.level,this.x,this.y-this.height/2);
    					
    					}
    				}
    				
    				
    				
    				
    				if(this.shootTime<this.shootRate){
						this.shootTime++;
					}else{
						this.shooting=false;
						this.shootTime=0;
						this.setROF();
					}
    				
    			}
    			/*
    			if(this.lifeTime%20 ==0){
    				this.h.setH(--this.h.health);
    			}
    			
				*/
				this.lifeTime++;
				//checkPOB(this,false);
			}
	};















/*

//check if point is out of bound
var checkPOB = function(ob,willDelete){
		//If it goes off the top or bottom edge
	if(ob.y < 0-ob.height/2){
		console.log("1");
		if(willDelete){
			world.removeChild(ob);
		}else{
			keepInBounds(ob,true,true);
		}
	}if(ob.y > canvas.height-ob.height/2){
		console.log("2");
		if(willDelete){
			world.removeChild(ob);
		}else{
			keepInBounds(ob,true,false);
		}
	}
	//If it goes off the left or right edge
	if(ob.x < 0-ob.width/2){
		console.log("3");
		if(willDelete){
			world.removeChild(ob);
		}else{
			keepInBounds(ob,false,true);
		}
	}if(ob.x > canvas.width-ob.width/2){
		console.log("4");
		if(willDelete){
			world.removeChild(ob);
		}else{
			keepInBounds(ob,false,false);
		}
	}
};











var keepInBounds = function(ob,isY,isUL){
	if(isY){
		if(isUL){
			ob.y = 0-ob.height/2; //Place it at the top
		}else{	
	    	ob.y = canvas.height-ob.height/2; //Place it at the bottom
	   }
	}else{
		if(isUL){
			ob.x = 0-ob.width/2; //Place it at the left
		}else{
			ob.x = canvas.width-ob.width/2; //Place it at the right6
		}
	}	
};


		*/
				
					
			
			
			
			
function healthBar(max,offset){
	this.maxH = max;
	this.health = max;

	this.b = new healthBarBottom(max*2,offset);
	this.t = new healthBarTop(max*2,offset);
	world.addChild(this);
}



function healthBarTop(max,offset){
	Sprite.call(this);
	this.width = max;
	this.height = 25;
	
	this.y =0+offset;
	this.xoffset = -this.width;
	this.x = canvas.width;
	this.image = Textures.load("http://www.colorhexa.com/880296.png");
	world.addChild(this);
}
healthBarTop.prototype = new Sprite();



function healthBarBottom(max,offset){
	Sprite.call(this);
	this.width = max;
	this.height = 25;
	this.x = canvas.width;
	this.y = 0+offset;
	this.xoffset = -this.width;
	this.image = Textures.load("http://www.colorhexa.com/00ffff.png");
	world.addChild(this);
	
}

healthBarBottom.prototype = new Sprite();





healthBar.prototype.setH =  function(newHealth){
		if(newHealth <0){
			newHealth = 0;
		}
		
		
		this.t.width= newHealth*2;
		this.health= newHealth;
		this.t.xoffset = -this.t.width;
		this.t.x=canvas.width;
		//this.t.image = Textures.load(this.healthColor());	
};



healthBar.prototype.healthColor = function(){
	
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


healthBar.prototype.upgH = function(newHealth){
	if(newHealth <0){
		newHealth = 0;
	}
	this.b.width=newHealth;
	this.b.xoffset = -this.b.width;
	this.b.x=canvas.width;
	this.setH(newHealth);
};

	
	
function wepPair(type, level){
	this.type = type;
	this.level = level;
}







