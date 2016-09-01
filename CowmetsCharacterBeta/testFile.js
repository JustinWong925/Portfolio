function Level(gameStorage){
	this.gs = gameStorage;	
	this.p = new MadCow(canvas.width/2,    canvas.height-100,   this.gs.pWepU,  this.gs.pWepT,   this.gs.pWepL,this.gs.pWepB);
	this.aM = new alienManager(this.p,false);
    this.pM = new PowerUpManager(this.p);
    this.rM = new rockManager(this.p,false);
    
    
	this.lifeTime = 0;
	this.hoardTimer = 100;
	
	this.pauseWait = 10;
	this.pressedPause = false;
}


Level.prototype.initialize = function(){
	world.addChild(this);
};






Level.prototype.update = function(d){

	if(!this.pressedPause){
		
		if(gInput.m){
			this.p.pauseP();
			this.aM.pause = !this.aM.pause;
			this.rM.pause = !this.rM.pause;
			this.pressedPause = true;
			
		}else{
			console.log("not pressed");
		}
	}
	
	
	
	
	
	
	
	
	if(this.p.pause){
		
	}
    if(this.pressedPause){
    	--this.pauseWait;
    	console.log("counting");
    	if(this.pauseWait<=0){
    		this.pauseWait = 50;
    		this.pressedPause = false;
    		console.log("done counting");
    	}
    }
    
    
    if(!this.p.pause){
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	if(this.lifeTime == 5){
    		this.aM.createF(canvas.width/2,-20,100);
    	}
    	
    	this.rM.setMax(20);
    	
    	
    	if(this.lifeTime==200){
    		console.log(this.rM.switchAuto());
    	}
    	
    	
    	
    	
    	
    	
    	if(this.lifeTime ==300){
    		this.rM.generateC(canvas.width+50,canvas.height/2, -100, 1, 1, 15,0.2,0.5,0.3);
    	}
    	if(this.lifeTime ==700){
    		console.log(this.rM.switchAuto());
    	}
    	
    	
    	if(this.lifeTime == 1000){
    		this.aM.createF(canvas.width/2,-20,200);
    	}
    	this.lifeTime++;
    	
    }else{
    	//draw pause menu
    }
};
Level.prototype.beginComet = function(){};
