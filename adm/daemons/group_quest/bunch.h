bunch place = "";
bunch the_nation = "";
bunch the_party = "";
bunch the_enemy = "";
int all = 0;
bunch name1,name2,name3;
mixed *story;

int select_quest();
bunch create_tiaoxin();
bunch jiuming();
int not_wizard(object ob);

nosave mixed *all_story = ({
({
        "place，繁华之地，name1，name2，name3一行三人正在逛街。",
        "一个流氓匆忙行路中，撞了name1一下，name1反手一个巴掌抽了过去。",
        "很快围上来好几个流氓，把name1团团围住。",
        "name2眼睛一瞪：『想干嘛？打架？』(卷袖子中...)",
        "流氓们相顾大笑，齐唰唰的抽出雪亮的钢刀，逼上前来。",
        "name2有些结巴：『我...我们...是...是...the_party的！你们别乱来！』",
        "几把钢刀当面劈将过来...",
        "name1吓了一跳，反身就跑，速度飞快...",
        "一个流氓飞出一把小刀，正中name1屁股，随着name1的狂奔上下颤抖。",
        "name2见钢刀劈过来，急忙闪身，衣襟给削掉一片，立刻掉头逃窜。",
        "走在最前面的name3听到声响，刚回头，看到name1，name2飞也似从身边窜过。",
        "后面一群流氓挥舞着钢刀叫喊着追杀过来！",
        "......",
        "name3后发先至，跑在name1，name2前面...",
        "三个人跑的上气不接下气，总算摆脱了流氓。",
        "一个时辰后...",
        "一群人手持兵器，冲入place，在大街小巷中四处搜索。",
        (: create_tiaoxin :),
        "据说the_enemy正在place集结，气势汹汹，决意要铲平the_party！",
}),
({
        "name1走在路上，迎面遇到name2，赶紧扬手打招呼。",
        "name2拉着name1的手，鬼鬼祟祟的扯到一个没人的角落。",
        "name1很惊奇，刚想发问，name2就竖起食指：『嘘！...』",
        "name2探头探脑地四下张望是否有其他人...",
        "『这是我前天从一个流氓尸体上搜出来的』，name2递给name1一本薄绢小册。",
        "name1随手翻了翻，眼珠子瞪得比牛铃还大！",
        "『这...这是什么东东？哇，你小子偷看春宫图？』name1惊奇的大叫起来。",
        "name2吓的赶紧捂住name1嘴巴：『小声！小声点！！』",
        "name2凑到name1耳边轻声说到：『看下面的注解，是the_enemy老大和他姘头哦！』",
        "name2窃窃贼笑：『那可是他手下小喽罗偷看了画出来的，不想到了我们手里，如何？逼真吧？』",
        "name1半天合不上嘴巴，突然叫道：『the_enemy老大干那事给人偷偷画下来了？』",
        "name2一把掐住name1脖子，龇牙咧嘴地说：『叫你小声点！还这么扯着嗓子嚷嚷，想死啊？』",
        "......",
        "name1面红气喘的被name2拖走了。",
        "一扇门打开了，一个脑袋伸出来左右顾盼，小声嘀咕：『出这么大的糗事？好在给我听到了！』",
        "过了数个时辰...",
        "一群人手持兵器，冲入place，大街小巷中四处搜索。",
        (: create_tiaoxin :),
        "据说the_enemy正在place集结，气势汹汹，决意要铲平the_party！",
}),
({
        "name1，name2上山打猎归来...",
        "name1：『你不是说山上有红狐狸么？怎么连根野鸡毛都没看到？』",
        "name2白白眼睛：『还不是你一路放屁，别说狐狸，老虎都给你臭跑了！』",
        "name1脸一红，不甘心地分辩着：『你自己也放了一个的，而且是最臭的那个！』",
        "name2飞起一脚，踹在name1的屁股上，name1一把扯住了name2的头发....",
        "两个人打架中......",
        "一个人走下山来，背后披着两张火红的狐狸皮。",
        "name1眼睛一亮，对着name2使了个眼神。",
        "name2心领神会，等陌生人走过身边，突然弯腰捡起一块石头冲他后脑勺就是狠狠一下子。",
        "name1冲上前，对准倒在地上的陌生人又用力踹了几脚！",
        "两个人得意的奸笑：『这下子不会两手空空地回去，让the_party的兄弟笑话了。』",
        "name1和name2一人提着一张狐狸皮扬长而去。",
        "......",
        "一群人手持兵器，冲入place，大街小巷中四处搜索。",
        (: create_tiaoxin :),
        "据说the_enemy正在place集结，气势汹汹，决意要铲平the_party！",
}),
({
        "name1走在路上，突然前面窜出一个彪形大汉，举着一把明晃晃的钢刀！",
        "『大爷我要你钱不要你的命，聪明的话就赶紧把钱袋给我！』",
        "name1两腿颤抖，掏出钱袋，彪形大汉一把抢过，扬长而去。",
        "name2，name3走来，看见name1脸色苍白，上前讯问事由。",
        "『靠，什么鸟胆子这么大，欺负到我们the_party头上了？！』，name2义愤填膺。",
        "name3冷冷一笑，一挥手：『追！』",
        "......",
        "三个人追上大汉，团团围住。",
        "name2突然弯身抓起一把泥土，劈面向大汉脸上洒去。",
        "name3乘大汉眼睛无法睁开，张开一个大麻布袋将大汉上半身套了进去，旋即收紧袋口。",
        "name1得意的大笑，操起一根棍子就没头没脸地狠揍。",
        "片刻之后，name3将麻布袋扯回来，大汉给揍得跟猪头一样。",
        "『给我记住，以后见到the_party的人最好躲着走路！』，name2扬手又送上了一个大嘴巴。",
        "name1将自己的钱袋掏了回来，顺带把大汉口袋里的散碎银两搜刮一空。",
        "三个人高高兴兴的去找馆子喝酒。",
        "片刻之后...",
        "一群人手持兵器，冲入place，大街小巷中四处搜索。",
        (: create_tiaoxin :),
        "据说the_enemy正在place集结，气势汹汹，决意要铲平the_party！",
}),
({
        "place。华灯初上，熙来攘往，正是一副热闹景象。",
        "梨香院内，莺歌燕语，觥筹交错，戏谑之声阵阵。",
        "name1、name2正在一间大房里据案大嚼，吃得大汗淋漓，满桌狼藉。",
        "门『吱呀』一声开了，name3走了进来：『哈哈，你们俩原来躲在这里。』",
        "name2放下手里啃剩的半条鸡腿，含混不清的道：『来来...一块吃点...』",
        "『两个土包子！』name3不屑的哼了一声：『这里是什么地方？就知道吃！』",
        "name1『咕嘟』一声喝干了碗里的酒，反手抽了自己一个嘴巴：",
        "『对啊，这里可是有姑娘的！』跟着高声嚷道：『来人！快来人！』",
        "龟奴应声而至，陪着笑道：『几位有何吩咐？』",
        "name3嘿嘿一笑，问龟奴道：『你们这里出名的粉头都有哪些？』",
        "龟奴恍然大悟，笑着说道：『我们这里的姑娘，可都是place数一数二的...』",
        "name1把眼一瞪，喝道：『哪来那么多废话，拣上好的快说！』",
        "龟奴陪笑道：『小雁姑娘、小翠姑娘、小春姑娘，最出名的要数小玉儿姑娘。』",
        "『好！』name2用力一拍桌子：『就把那个最出名的小玉儿给我叫来！』",
        "『这......』龟奴为难道：『小玉儿姑娘今天给人包啦，在陪隔壁那位爷呢！』",
        "『我呸！』name3一脚踹开龟奴，嚷道：『什么鸟人敢跟我们the_party抢粉头！』",
        "三人一涌而出，跟着就听见隔壁房内传来阵阵『噼啪！嘭嘭！哎哟！』的声音...",
        "一个被扁得象猪头炳的人从房内窜出，抱头落荒而逃，背后是三人得意的笑声...",
        "半个时辰之后，一伙人手持刀枪棍棒，气势汹汹的冲入place。",
        (: create_tiaoxin :),
        "据说the_enemy正在place集结，气势汹汹，决意要铲平the_party！",
}),
({
        "阴暗的小巷，污水四溢，垃圾遍地。",
        "一个身穿灰衣的男子喘着粗气奔了进来，身上几处伤口不断滴着鲜血。",
        "身后数道黑影随即掩至，挥舞手中明晃晃的钢刀，将灰衣人逼在了墙角。",
        "name1朝灰衣人『嘿嘿』奸笑了两声：『跑？看你这回还能跑到哪里去！』",
        "name2恶狠狠的道：『相好的，乖乖将东西双手奉上，我们就留你一条全尸！』",
        "灰衣人背靠墙壁，嘶声道：『你们好大的胆子！我们老大不会放过你们的！』",
        "name3一听大怒：『敬酒不吃吃罚酒，好，我送你上路！』（手中钢刀一挥）",
        "灰衣人惨叫一声，倒在了血泊之中。",
        "name1上前将灰衣人身上里里外外搜索了一通，从其口袋里找出一张纸片。",
        "『哇...』name3和name2立时围了过来：『藏宝图！这下我们the_party发达喽！』",
        "name1小心翼翼的藏起那张纸片，把手一挥：『此地不宜久留，风紧，扯呼！』",
        "三人擦掉钢刀上的血迹，转身急匆匆的离开了巷子。",
        "血泊中的灰衣人忽然动了动，原来并未死透。",
        "灰衣人挣扎着用手指在地上写了几个字，随即头一歪，就此断气。",
        "数日之后......",
        "一群人手持兵器，气势汹汹的冲入place。",
        (: create_tiaoxin :),
        "据说the_enemy正在place集结，气势汹汹，决意要铲平the_party！",
}),
({
        "风掠过河面，涟漪点点。",
        "name1站在河边，泪流满面。",
        "name2与name3恰于此时经过，见状大讶，问曰：『何故这般模样？』",
        "name1哭诉道：『昨日在place赌场出千失风，被the_enemy的人当场逮到，一顿暴扁。』",
        "伸手指着自己满头肿包，又道：『他们要我三日内赔银千两，否则便要砍我只手。』",
        "说罢嚎啕大哭，作势便要跃向河中，一边嚷着：『不如让我死了干净......』",
        "name2急忙拉住name1，劝道：『有事好说，有事好说，先不忙寻死觅活。』",
        "name3在一旁早听得七窍生烟、暴跳如雷，哇哇怪叫道：",
        "『想我们the_party，也算是江湖上响当当的字号，怎么能让人如此欺辱？』",
        "name2连连点头：『不错，怎能如此丢人？走，我们同去，拆了那家赌场！』",
        "name1顿时破涕为笑，将手一挥：『同去！同去！拆了那赌场！』",
        "三人闯入赌场，一番拳打脚踢、刀剁斧砍，直搅得鸡飞狗跳、鬼哭狼嚎......",
        "the_enemy自然咽不下这口恶气，数日过后，立即纠集人马兴师动众前来报复。",
        (: create_tiaoxin :),
        "据说the_enemy正在place集结，气势汹汹，决意要铲平the_party！",
}),
({
        "路旁桃花如云，枝头硕果累累，好大一片桃林。",
        "name1、name2和name3赶路经过此处，不禁馋涎遍地，立时扑入林中。",
        "『呼哧呼哧......』name2埋头大嚼，襟前汁水淋漓。",
        "name3打了个饱嗝，心满意足的叹道：『......爽......』",
        "『好吃！再来一个！』name1用力将啃得精光的桃核丢向远处，又伸出手去。",
        "三人正吃得酣畅间，忽然来了两名家丁模样的人。",
        "家丁甲（怒视三人）：『喂！这里是私人产业，你们怎能随意闯入！』",
        "家丁乙捋起袖子：『瞎了眼的东西，竟敢偷吃我们的东西，看打！』",
        "『砰碰！嗖......啪哒！』一条人影凌空飞起，摔入树丛内。",
        "随即又见一人在地上直滚向前，一头撞在树根上，顿时鼻青脸肿。",
        "『打？哈哈哈哈......』三人相视大笑。",
        "林外传来两名家丁逐渐远去的声音：『有种的别跑......等着瞧......』",
        "name1望着两名家丁的背景沉思道：『刚才我们是人多欺负人少......』",
        "『要是那两个家伙找来一大群帮手，我们岂不是要吃亏？』name2省悟过来。",
        "name3连连点头：『有理有理，还是及早开溜为妙。』",
        "三人急忙匆匆离去......",
        "过不多时，两名家丁果然带着大队人马，手持刀枪棍棒杀到。",
        "『不知死活的东西，快快出来领死！』",
        "『人呢？哪去了！』",
        "『看这满地脚印，似乎是逃向place了。』",
        "『追！』",
        "一群人手持兵器，气势汹汹的冲入place。",
        (: create_tiaoxin :),
        "据说the_enemy正在place集结，气势汹汹，决意要铲平the_party！",
}),
});
