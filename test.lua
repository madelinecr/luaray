s = Scene()
c = Camera(1280, 800, s)

sphere1 = sphere(150,500,20,35,2,3,1)
sphere2 = sphere(300,500,20,95,0,1,2)
alight = light(Vec3(300,-500,20), 8)

s:add_sphere(sphere1)
s:add_sphere(sphere2)
s:add_light(alight)

c:render()
