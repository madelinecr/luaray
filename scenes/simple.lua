s = Scene()
c = Camera(1280, 800, s)

object = Sphere(Vec3(550,300,20),Color(8,1,1),100)
alight1 = light(Vec3(300,300,20), 8)
alight2 = light(Vec3(800,800,20), 2)

s:add_object(object)
s:add_light(alight1)
s:add_light(alight2)

c:render()
