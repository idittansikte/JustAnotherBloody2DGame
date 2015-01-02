-- factory functions
function Health(t) return { total = t[1], regeneration = t[2] } end
function Animation(t) return { spritesheet = t[1], animations = t[2] } end
function Spritesheet(t)
    return { filename = t[1], width = t[2], height = t[3] }
end
function Animations(t)
    return { name = t[1], coords = t[2], duration = t[3] }
end

-- game entity class prototype and constructor
GameEntity = {}
setmetatable(GameEntity, {
    __call = function(self, t)
        setmetatable(t, self)
        self.__index = self
        return t
    end,
})

-- example game entity definition
entity = GameEntity{
    "ZombieFighter",
    Components = {
        Health{ 100, 0.1, },
        Animation{
            Spritesheet{ "spritesheet.gif", 80, 80 },
            Animations{
                {"stand",  {0,0,1,0,2,0,3,0}, 0.10},
                {"walk",   {4,0,5,0,6,0,7,0}, 0.10},
                {"attack", {8,0,9,0,10,0},    0.08},
            },
        },
    }
}

-- recursively walk the resulting table and print all key-value pairs
function print_table(t, prefix)
    prefix = prefix or ''
    for k, v in pairs(t) do
        print(prefix, k, v)
        if 'table' == type(v) then
            print_table(v, prefix..'\t')
        end
    end
end    
print_table(entity)

