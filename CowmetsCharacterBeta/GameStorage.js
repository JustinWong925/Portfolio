function GameStorage(levels){
	
	

	this.seconds = 0;
	this.lifeTime = 0;
	
	
	
	
	this.scoreBox = new TextBox();
	this.scoreBox.x = 10;
	this.scoreBox.y = 10;
	this.scoreBox.fontSize = 32;
	world.addChild(this.scoreBox);
	
	
	this.imArr = new Array();
	
	
		
		
		
	this.maxGridCellX=20;
	this.maxGridCellX=20;
	
	
	this.maxGridCellX=20;
	this.maxGridCellY=20;
	
	this.maxnumcells=40;
	

	
	
    this.pWepT = "ammo";
    this.pWepL = "0";
    this.pWepB = false;
    this.pWepU = null;
    this.currLevel = 0;
	
	//x
	gInput.addBool(88,"x");
	//m
	gInput.addBool(77, "m");
	//space
	gInput.addBool(32, "space");
	//shift
	gInput.addBool(16, "shift");

	//A
	gInput.addBool(65, "left");
	//D
	gInput.addBool(68, "right");
	//S
	gInput.addBool(83, "down");
	//W
	gInput.addBool(87, "up");
	
	//q
	gInput.addBool(89, "q");
	//e
	gInput.addBool(69, "e");
	
	//left key
	gInput.addBool(37, "left2");
	//right key
	gInput.addBool(39, "right2");
	//down key
	gInput.addBool(40, "down2");
	//up key
	gInput.addBool(38, "up2");
	world.addChild(this);
}

GameStorage.prototype.initialize = function (d){
	
	
};


GameStorage.prototype.update = function (d){
	this.seconds += (d*MSPF)/1000;
	this.lifeTime++;
	this.scoreBox.text = Math.round(this.time);

};

























function check2Ob(ob1, ob2) {
    var minX = ob1.x - ob1.width/2;;
    var maxX = ob1.x + ob1.width/2;
    var minY = ob1.y - ob1.height/2;
    var maxY = ob1.y + ob1.height/2;

    var minX2 = ob2.x - ob2.width/2;;
    var maxX2 = ob2.x + ob2.width/2;
    var minY2 = ob2.y - ob2.height/2;;
    var maxY2 = ob2.y + ob2.height/2;


    if (maxX2 >= minX && minX2 <= maxX && maxY2 >= minY && minY2 <= maxY) {
        return true;
    }
    return false;
}





//check if point is out of bound
var checkPOB = function(ob,willDelete){
		//If it goes off the top or bottom edge
	if(ob.y < 0+ob.height/2){
		//console.log("1");
		if(willDelete){
			world.removeChild(ob);
		}else{
			keepInBounds(ob,true,true);
		}
		
	}if(ob.y > canvas.height-ob.height/2){
		//console.log("2");
		if(willDelete){
			world.removeChild(ob);
		}else{
			keepInBounds(ob,true,false);
		}
		
	}
	//If it goes off the left or right edge
	if(ob.x < 0+ob.width/2){
		//console.log("3");
		if(willDelete){
			world.removeChild(ob);
		}else{
			keepInBounds(ob,false,true);
		}
		
	}if(ob.x > canvas.width-ob.width/2){
		//console.log("4");
		if(willDelete){
			world.removeChild(ob);
		}else{
			keepInBounds(ob,false,false);
		}
		
	}
	
};



//check if point is out of bound
var checkPOBn = function(ob){
		//If it goes off the top or bottom edge
	if(ob.y+ob.height/2 < -200){
		
		
		
		//console.log("top");
		return true;
		
	}
	
	if(ob.y-ob.height/2 > canvas.height+50){
		//console.log("bottom");
		return true;
		
	}
	
	
	//If it goes off the left or right edge
	if(ob.x+ob.width/2 < -100){
		//console.log("left");
		return true;
		
	}if(ob.x-ob.width/2  > canvas.width+100){
		//console.log("right");
		return true;
		
	}
	return false;
};






