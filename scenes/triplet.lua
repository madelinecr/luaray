s = Scene()
c = Camera(1280, 800, s)

sphere1 = Sphere(Vec3(550,300,20),Color(4,10,1),35)
sphere2 = Sphere(Vec3(400,100,20),Color(8,1,2),65)
sphere3 = Sphere(Vec3(450,450,20),Color(0,1,4),45)
light1 = light(Vec3(300,300,20), 8)
light2 = light(Vec3(900,900,20), 20)

s:add_object(sphere1)
s:add_object(sphere2)
s:add_object(sphere3)
s:add_light(light1)
s:add_light(light2)

c:render()
