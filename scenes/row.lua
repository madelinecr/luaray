s = Scene()
c = Camera(1280, 800, s)

sphere1 = Sphere(Vec3(300,450,20),Color(5,5,3),20)
sphere2 = Sphere(Vec3(600,450,20),Color(10,10,1),50)
sphere3 = Sphere(Vec3(900,450,20),Color(10,1,10),100)
light1 = light(Vec3(100,400,20),20)
light2 = light(Vec3(200,600,20),15)
light3 = light(Vec3(1400,200,20),10)

s:add_object(sphere1)
s:add_object(sphere2)
s:add_object(sphere3)
s:add_light(light1)
s:add_light(light2)
s:add_light(light3)

c:render()
