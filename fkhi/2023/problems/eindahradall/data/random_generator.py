import random
import sys

divarr = [
	962058861484320600,
	930515947993031400,
	840021796602588600,
	768530579870453400,
	681527117998326600,
	612219275490022200,
	592146512359201800,
	589802538040115400,
	523032439394064600,
	469842699794668200,
	454438021112875800,
	478519040296697400,
	429856087046185800,
	415762444847950200,
	381193133795674200,
	368694998261389800,
	331200591658536600,
	988110745547725800,
	876249151712134200,
	787139068487171400,
	761331230176116600,
	993601774975609800,
	393201692026743600,
	348688292929376400,
	313228466529778800,
	302958680741917200,
	319012693531131600,
	286570724697457200,
	277174963231966800,
	254128755863782800,
	245796665507593200,
	220800394439024400,
	922236695844544080,
	817832541597991920,
	734663130588026640,
	710575814831042160,
	720018682802218800,
	658740497031817200,
	584166101141422800,
	524759378991447600,
	507554153450744400,
	939685399589336400,
	908876042225751600,
	957038080593394800,
	859712174092371600,
	831524889695900400,
	762386267591348400,
	737389996522779600,
	662401183317073200,
	432011209681331280,
	395244298219090320,
	350499660684853680,
	314855627394868560,
	304532492070446640,
	707763045648138480,
	627638927272877520,
	563811239753601840,
	545325625335450960,
	574222848356036880,
	515827304455422960,
	498914933817540240,
	457431760554809040,
	442433997913667760,
	397440709990243920,
	505545032605813200,
	448313519480626800,
	402722314109715600,
	389518303811036400,
	410159177397169200,
	368448074611016400,
	356367809869671600,
	326736971824863600,
	316024284224048400,
	283886221421602800,
	321710475294608400,
	285290421487671600,
	256277836251637200,
	247875284243386800,
	261010385616380400,
	234466956570646800,
	226779515371609200,
	207923527524913200,
	201106362688030800,
	180654868177383600,
	966152728979998560,
	856776948340753440,
	769647089187456480,
	744412758394425120,
	672017437282070880,
	614824463896362720,
	545221694398661280,
	489775420392017760,
	473717209887361440,
	480012455201479200,
	439160331354544800,
	389444067427615200,
	349839585994298400,
	338369435633829600,
	786403384053487200,
	697376585858752800,
]

primarr = [
    999999999999996461,
    999999999999996467,
    999999999999996553,
    999999999999996647,
    999999999999996659,
    999999999999996673,
    999999999999996701,
    999999999999996757,
    999999999999996767,
    999999999999996773,
    999999999999996781,
    999999999999996791,
    999999999999996829,
    999999999999996839,
    999999999999996847,
    999999999999996871,
    999999999999996881,
    999999999999996917,
    999999999999996967,
    999999999999997013,
    999999999999997019,
    999999999999997033,
    999999999999997057,
    999999999999997079,
    999999999999997121,
    999999999999997133,
    999999999999997189,
    999999999999997207,
    999999999999997313,
    999999999999997427,
    999999999999997433,
    999999999999997457,
    999999999999997471,
    999999999999997499,
    999999999999997589,
    999999999999997651,
    999999999999997751,
    999999999999997817,
    999999999999997831,
    999999999999997837,
    999999999999997883,
    999999999999997901,
    999999999999997943,
    999999999999997951,
    999999999999997961,
    999999999999997993,
    999999999999997999,
    999999999999998021,
    999999999999998027,
    999999999999998143,
    999999999999998167,
    999999999999998171,
    999999999999998227,
    999999999999998237,
    999999999999998269,
    999999999999998273,
    999999999999998321,
    999999999999998443,
    999999999999998539,
    999999999999998581,
    999999999999998651,
    999999999999998653,
    999999999999998743,
    999999999999998759,
    999999999999998867,
    999999999999998927,
    999999999999998929,
    999999999999998939,
    999999999999998989,
    999999999999999023,
    999999999999999073,
    999999999999999079,
    999999999999999121,
    999999999999999157,
    999999999999999161,
    999999999999999283,
    999999999999999331,
    999999999999999359,
    999999999999999371,
    999999999999999409,
    999999999999999419,
    999999999999999443,
    999999999999999463,
    999999999999999487,
    999999999999999503,
    999999999999999529,
    999999999999999539,
    999999999999999569,
    999999999999999601,
    999999999999999613,
    999999999999999631,
    999999999999999637,
    999999999999999709,
    999999999999999737,
    999999999999999749,
    999999999999999829,
    999999999999999863,
    999999999999999877,
    999999999999999967,
    999999999999999989,
]

mixsq = [
    999999600000040000,
    999999683000023400,
    999999693000021400,
    999999729000014200,
    999999737000012600,
    999999683000023400,
    999999766000013689,
    999999776000012519,
    999999812000008307,
    999999820000007371,
    999999693000021400,
    999999776000012519,
    999999786000011449,
    999999822000007597,
    999999830000006741,
    999999729000014200,
    999999812000008307,
    999999822000007597,
    999999858000005041,
    999999866000004473,
    999999737000012600,
    999999820000007371,
    999999830000006741,
    999999866000004473,
    999999874000003969,
]

random.seed(sys.argv[-1])
opt = int(sys.argv[1])

if opt > 0:
    if opt < 100:
        print(opt)
        for i in range(1, opt + 1):
            print(i)
    else:
        print(100)
        for i in range(100):
            print(random.randint(1, opt))
elif opt == -1:
    print(100)
    for x in divarr:
        print(x)
elif opt == -2:
    print(100)
    for x in primarr:
        print(x)
elif opt == -3:
    print(100)
    for i in range(100):
        if random.randint(1, 3) == 1:
            print(random.randint(1, 10 ** 18))
        elif random.randint(1, 2) == 1:
            print(random.choice(divarr))
        else:
            print(random.choice(primarr))
else:
    print(100)
    for i in range(75):
        print(random.randint(1, 10 ** 9 - 1) * (10 ** 9 + 7))
    for x in mixsq:
        print(x)
