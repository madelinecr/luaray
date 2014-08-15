s = Scene()
c = Camera(1280, 800, s)

sphere1 = sphere(Vec3(550,300,20),100,8,1,1)
alight1 = light(Vec3(300,300,20), 8)
alight2 = light(Vec3(800,800,20), 2)

s:add_sphere(sphere1)
s:add_light(alight1)
s:add_light(alight2)

c:render()
