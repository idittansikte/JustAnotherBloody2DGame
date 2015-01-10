Platform = {
    NORMAL = {
	Spritesheet = "imgs/block.png",
	Size = { 100, 100 },
	Collisionbox = {7,20,79,79},
	Immune = false,
	Health = 300,
	Damage = 0,
	DamageTicks = 100, -- milliseconds
	Friktion = 5, -- 1 - 9 higher value = slower
	JumpAcceleration = 8,
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
	Damage = 10,
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
	Damage = 40,
	----------------
	Ranger = true,
	Projectile = "SLOWFIREBALL", --if ranger else ignored
	----------------
	TargetPlayer = true,
	Intervall = 1000,	-- Intervall of attack
	AggroDistance = 400, -- if TargetPlayer else ignored
	MinAttackRange = 200, -- NOT IMPLEMENTED YET-- if TargetPlayer else ignored
	----------------
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
	Spritesheet = "imgs/player.png",
	Size = { 50, 50 },
	Collisionbox = {0,12,40,40},
	Immune = false,
	Health = 1000,
	Damage = 70,
	Projectile = "FIREBALL", --if ranger else ignored
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
    
Projectile = {
	
    FIREBALL = {
	Spritesheet = "imgs/bullet.png",
	Size = { 20, 20 },
	Collisionbox = {0,0,20,20},
	Immune = true,
	Health = 300,
	Distance = 800,
	Speed = 15, -- Pixels per frame
	Animations = {
	    INAIR = {
		Spritesheet = "imgs/vogel.png",
		FramePositions = { 0,0, 100,0, 200,0, 300,0 ,400,0 },
		FrameSize = { 100, 70 },
		ScreenSize = {0,0,100,70},
		Delay = 50, -- Millisekunder
		DoOnce = false,
	    },
	    DEATH = { -- Dont change name if you dont know what you're doin...
		Spritesheet = "imgs/bullet_dies.png",
		FramePositions = { 0,0, 20,0, 40,0, 60,0 },
		FrameSize = { 20, 20 },
		ScreenSize = {0,0,20,20},
		Delay = 100, -- Millisekunder
		DoOnce = true,
	    },
	},
    },
    
    SLOWFIREBALL = {
	Spritesheet = "imgs/bullet_ice.png",
	Size = { 20, 20 },
	Collisionbox = {0,0,20,20},
	Immune = true,
	Health = 300,
	Distance = 800,
	Speed = 6, -- Pixels per frame
	Animations = {
	    INAIR = {
		Spritesheet = "imgs/vogel.png",
		FramePositions = { 0,0, 100,0, 200,0, 300,0 ,400,0 },
		FrameSize = { 100, 70 },
		ScreenSize = {0,0,100,70},
		Delay = 50, -- Millisekunder
		DoOnce = false,
	    },
	    DEATH = { -- Dont change name if you dont know what you're doin...
		Spritesheet = "imgs/bullet_dies.png",
		FramePositions = { 0,0, 20,0, 40,0, 60,0 },
		FrameSize = { 20, 20 },
		ScreenSize = {0,0,20,20},
		Delay = 100, -- Millisekunder
		DoOnce = true,
	    },
	},
    },
	
}

Powerup = {
    
    Health = {
	
    },
    
    Damageup = {
	
    },
    
    Speedup = {
	
    },
    
    Projectile = {
	
    },
}

Item = {
    
    Coin = {
	
    },
}


