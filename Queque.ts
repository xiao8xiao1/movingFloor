class Queque extends egret.DisplayObjectContainer{//class begin

movingFloor : Floor;
gameFloors : Floor[] = [];
floorHeight: number = 30;
twLoop: egret.Tween;
twFall: egret.Tween;
fallLen: number;
score:number = 0;
scoreLabel:egret.TextField;
_icon:egret.Shape;
public constructor() {
	super();
	this.addEventListener(egret.Event.ADDED_TO_STAGE,this.onAddToStage,this);
}
private onAddToStage(event:egret.Event)	{
	let stageW = egret.MainContext.instance.stage.stageWidth;
	let stageH = egret.MainContext.instance.stage.stageHeight;

	let topMask = new egret.Shape();
	topMask.graphics.beginFill(0xffffff, 0.5);
	topMask.graphics.drawRect(0, 0, stageW, stageH);
	topMask.graphics.endFill();
	this.addChild(topMask);

	this.scoreLabel = new egret.TextField(); 
	this.score;
	this.scoreLabel.text = (this.score++).toString();
	this.addChild( this.scoreLabel );

	var btn1 = new egret.Shape();
	btn1.graphics.beginFill(0x0000cc, 0.8);
	btn1.graphics.drawRect(0, 0, 100, 60);
	btn1.graphics.endFill();
	btn1.x =30;
	btn1.touchEnabled = true;
	btn1.addEventListener(egret.TouchEvent.TOUCH_TAP,this.BiggerMovingFloor,this);
	this.addChild(btn1);

	let initWidth = stageW/4;
	let floor = new Floor(stageW/2 - initWidth/2, stageW/2 + initWidth/2, stageH/2, this.floorHeight);
	this.addChild(floor);
	this.gameFloors.push(floor);

	this.movingFloor = new Floor(stageW/2 - initWidth/2, stageW/2 + initWidth/2, stageH/2 - this.floorHeight, this.floorHeight);
	this.addChild(this.movingFloor);

	this.twLoop = egret.Tween.get(this.movingFloor, { loop:true} );

	this.twLoop.to( {x:0}, 500);//, egret.Ease.sineIn);
	this.twLoop.to( {x:stageW/2 - initWidth/2}, 500);//, egret.Ease.sineOut );
	this.twLoop.to( {x:stageW - initWidth}, 500);//, egret.Ease.sineIn );
	this.twLoop.to( {x:stageW/2 - initWidth/2}, 500);//, egret.Ease.sineOut );

	this.touchEnabled = true;
	this.addEventListener( egret.TouchEvent.TOUCH_TAP, this.onTouch, this );		
}
private onTouch( evt:egret.TouchEvent )
{
	let topFloor = this.gameFloors[this.gameFloors.length - 1];
	let l = this.movingFloor.x;
	let r = l + this.movingFloor.scaleX;
	let L = topFloor.x;
	let R = L + topFloor.scaleX;
	let [dropL, dropR, deleL, deleR, dele2L, dele2R] = [0,0,0,0,0,0];

	if (r <= L || l >= R)
	{return;}

	if (l < L && r > L && r <= R)
	{
		[dropL, dropR] = [L, r];
		[deleL, deleR] = [l, L];
	}
	else
	if (l < L && r > R)
	{
		[dropL, dropR] = [L, R];
		[deleL, deleR] = [l, L];
		[dele2L, dele2R] = [R, r];
	}
	else 
	if (l == L && r <= R)
	{
		[dropL, dropR] = [L, r];
	}
	else 
	if (l == L && r > R)
	{
		[dropL, dropR] = [L, R];
		[deleL, deleR] = [R, r];
	}
	else
	if (l > L && r <= R)
	{
		[dropL, dropR] = [l, r];
		[deleL, deleR] = [L, l];
	}
	else
	if (l > L && r > R)
	{
		[dropL, dropR] = [l, R];
		[deleL, deleR] = [R, r];
	}

	let dropFloor = new Floor(dropL, dropR, this.movingFloor.y,  this.floorHeight);
	dropFloor.color = Math.floor(Math.random() * 256) << 16 ;
	this.gameFloors.push(dropFloor);
	this.addChild(dropFloor);
	this.StartFalling();
	this.movingFloor.scaleX = dropR - dropL;
	
	this.spawnDeleFloor(deleL, deleR);
	this.spawnDeleFloor(dele2L, dele2R);
	this.scoreLabel.text = (++this.score).toString();
}
private spawnDeleFloor(deleL:number, deleR:number)
{
	if (!(deleL == 0 && deleR == 0)){
		let delFloor = new Floor(deleL, deleR, this.movingFloor.y,  this.floorHeight);
		delFloor.color = Math.floor(Math.random() * 256) ;
		this.addChild(delFloor);
		let tw = egret.Tween.get(delFloor);
		tw.wait(500)
			.to( {y:0}, 5000 )
			.call(function(floor: Floor){ 
					this.removeChild(floor)
				}, this, [delFloor]
			)
	}
	
}
private BiggerMovingFloor( evt:egret.TouchEvent )
{
	this.gameFloors[this.gameFloors.length - 1].scaleX += 50;
	this.movingFloor.scaleX += 50;
	evt.stopImmediatePropagation();
}

private  StartFalling()	{
	this.touchEnabled = false;
	this.movingFloor.visible = false;
	this.twLoop.setPaused(true);

	this.fallLen = 0;
	for (var i = 0; i < this.gameFloors.length; ++i) {
		this.gameFloors[i].startY = this.gameFloors[i].y;
	}

	this.twFall = egret.Tween.get(this,{ onChange:this.TickFalling, onChangeObj:this } );
	this.twFall.wait(500)
				.to( {fallLen:this.floorHeight}, 1000 )
				.call(this.FinishFalling, this);

}
private  TickFalling()	{
	for (var i = 0; i < this.gameFloors.length; ++i) {
		this.gameFloors[i].y = this.gameFloors[i].startY + this.fallLen;
	}
	
}
private  FinishFalling()	{
	this.touchEnabled = true;
	this.movingFloor.visible = true;
	this.twLoop.setPaused(false);
}

private AddScore(){
}


}//class end
