s = Scene()
c = Camera(1280, 800, s)

sphere1 = sphere(Vec3(550,300,20),35,4,10,1)
sphere2 = sphere(Vec3(400,100,20),65,8,1,2)
sphere3 = sphere(Vec3(450,450,20),45,0,1,4)
light1 = light(Vec3(300,300,20), 8)
light2 = light(Vec3(900,900,20), 4)

s:add_sphere(sphere1)
s:add_sphere(sphere2)
s:add_sphere(sphere3)
s:add_light(light1)
s:add_light(light2)

c:render()
