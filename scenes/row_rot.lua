s = Scene()
c = Camera(1280, 800, s)

sphere1 = Sphere(Vec3(300,150,10),Color(5,5,3),20)
sphere2 = Sphere(Vec3(600,300,20),Color(10,10,1),50)
sphere3 = Sphere(Vec3(900,450,30),Color(10,1,10),100)
light1 = light(Vec3(100,300,0),20)
light2 = light(Vec3(1200,600,40),15)
light3 = light(Vec3(100,150,0),20)
light4 = light(Vec3(100,50,0),20)


s:add_object(sphere1)
s:add_object(sphere2)
s:add_object(sphere3)
--s:add_light(light1)
s:add_light(light2)
--s:add_light(light3)
--s:add_light(light4)


c:render()
