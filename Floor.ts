class Floor extends egret.Shape {
	startY: number;
	color:number = 0xff0101;
	public constructor(l: number = 0, r: number = 0,  y: number = 0, height: number = 30) {
		super()
		this.x = l;
		this.y = y;
		this.width = 1;
		this.height = height;
		this.scaleX = r - l;
		this.addEventListener(egret.Event.ADDED_TO_STAGE,this.draw,this);
	}
	
	public draw()	{
		this.graphics.beginFill(this.color, 0.5);
		this.graphics.drawRect(0, 0, this.width, this.height);
		this.graphics.endFill();
	}
}