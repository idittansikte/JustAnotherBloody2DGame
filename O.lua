Platform = {
    NORMAL = {
	Spritesheet = "imgs/block.png",
	Size = { 100, 100 },
	Collisionbox = {7,20,79,79},
	Immune = true,
	Health = 300,
	Damage = 0,
	DamageTicks = 100, -- milliseconds
	Friktion = 5, -- 1 - 9 higher value = slower
	JumpAcceleration = 5,
	Animations = {
	    DEATH = { -- Dont change name if you dont know what you're doin...
		Spritesheet = "imgs/block3d_dies.png",
		FramePositions = { 0,0, 100,0, 200,0, 300,0 ,400,0, 500,0, 600,0, 700,0 },
		FrameSize = { 100, 300 },
		ScreenSize = {0,0,100,300},
		Delay = 100, -- Millisekunder
		DoOnce = true,
		},
	},
    },
	
    FIRE = {
    	Spritesheet = "imgs/block_fire.png",
	Size = { 100, 100 },
	Collisionbox = {7,20,79,79},
	Immune = true,
	Health = 300,
	Damage = 1,
	DamageTicks = 100, -- milliseconds
	Friktion = 2, -- 1 - 9 :: higher value = slower
	JumpAcceleration = 15,
	Animations = {
	    DEATH = { -- Dont change name if you dont know what you're doin...
		Spritesheet = "imgs/block_fire_dies.png",
		FramePositions = { 0,0, 100,0, 200,0, 300,0 ,400,0, 500,0, 600,0, 700,0 },
		FrameSize = { 100, 300 },
		ScreenSize = {0,0,100,300},
		Delay = 100, -- Millisekunder
		DoOnce = true,
		},
	},
    },
    --
    --GRASS = {
    --
    --},
    
}
    
Enemy = {
	
	--Golem = {
	--    
	--},
	
	Crow = {
	    Spritesheet = "imgs/vogel.png",
	    Size = { 100, 70 },
	    Collisionbox = {0,0,100,70},
	    Immune = false,
	    Health = 600,
	    Damage = 1,
	    Attack = "FIREBALL",
	    Intervall = 2000,
	    Target = "PLAYER", --PLAYER OR NONE
	    AggroDistance = 600,
	    ApplyGravitation = false, -- Fall or not
	    Animations = {
		WALK = {
		    Spritesheet = "imgs/vogel.png",
		    FramePositions = { 0,0, 100,0, 200,0, 300,0 ,400,0 },
		    FrameSize = { 100, 70 },
		    ScreenSize = {0,0,100,70},
		    Delay = 50, -- Millisekunder
		    DoOnce = false,
		},
		DEATH = { -- Dont change name if you dont know what you're doin...
		    Spritesheet = "imgs/vogel_dies.png",
		    FramePositions = { 0,0, 100,0, 200,0, 300,0 ,400,0, 500,0, 600,0 },
		    FrameSize = { 100, 800 },
		    ScreenSize = {0,0,100,800},
		    Delay = 100, -- Millisekunder
		    DoOnce = true,
		},
	    },
	},   
}
    
Player = {
	Hero = {
	    
	},
}
    
Attack = {
	
	Fire_Strike = {
	    
	    
	},
	
}
