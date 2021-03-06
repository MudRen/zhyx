// fuyu-shengong by yuchang@zhyx
 

#include <ansi.h>

inherit FORCE;

string *xue_name = ({ 
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴", "承浆穴", "天突穴", "百会穴",
"幽门穴", "章门穴", "大横穴", "紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", });

string *attack_name = ({
"天意诀剑气", "地势诀剑气", "君王诀玄劲", "金断诀玄劲", });

string *dodge_msg = ({
       "$n人如大鸟般跃起，平飞掠出，轻轻一点，宛似飞燕在天空一折，又掠了出去。\n",
       "$n身未回，身形却地倒飞而出，宛若流星，斜挂纵落。\n",
       "$n一点，又疾地冲天而起，去势劲急，$n在骄阳下映耀，犹如孔雀开屏，破空而去。\n",
       "就在这一霎眼间，$n倏然不见了，一阵凤掠过，扬柳飞送。\n",
        "$n施展了“覆雨神功”中的“月映”法，在月色寒光中消失了。\n",   
       "剑割微风，造成急卷的气流割体,$n轻如落叶，已飘到$N背后。正是以"+HIW"“风流”"NOR+"一诀\n",
});

string *parry_msg = ({
       "$n以"+MAG"「师教诀」"NOR+"之势，竟随在$N之后,竟让$N产生一种错觉.\n",
      "$n在这刹那间，身体变得如一根朽木。在这瞬间将所有的穴道全部闭死.正是"+HIM"「木顽诀」NOR\n",
       "$n运用"+CYN"「水逝诀」"NOR+"在$n周围激起了无数串水柱，$N的武器全打在水墙上，都无法透过.\n",
        "$n仗着遥远的火光摇晃，以"+RED"「火延诀」"NOR+"之势，掩人眼目,急闪一旁.\n",
        "$n用"+YEL"「土掩诀」"NOR+"迅速的在地上掘开洞,$n不见了\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("fuyu-shengong", 1);
        return lvl * lvl * 10 * 35 / 100 / 200;
}

mapping *actionf = ({
([      "action": "$N使出覆雨神功中的"+HIY"「天意诀」"NOR+"$N已仿佛与天融合在一起，在刹那间便是苍苍天穹，永无底止，也没有感情。\n" NOR,
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "天意诀剑气" NOR,
        "damage_type":  "内伤"
]),
([      "action": "$N使出覆雨神功中的"+HIW"「地势诀」"NOR+"，$N立时觑出死角，觅得虚隙，乘机而入\n" NOR,
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIR "地势诀剑气" NOR,
        "damage_type":  "割伤"
]),
([      "action": "$N" HIY "举剑齐眉，容庄神凝，$w剑尖凝在半空，遥指$n。使出覆雨神功中的"+HIR"「君王诀」" NOR+"\n" NOR,
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIY "君王诀玄劲" NOR,
        "damage_type":  "刺伤"
]),
([      "action": "$N" WHT "使出覆雨神功中的"+HIB"「亲思诀」"NOR+"，以一些声音、手势、音乐、景象吸引住$n，以惊人数倍的内力，使$n坠入了往事尘烟之中\n" NOR,
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "亲思诀玄劲" NOR,
        "damage_type": "内伤"
]),
([      "action": "$N" HIW "使出覆雨剑法中的"+HIC"「金断诀」"NOR+"，倏地一个箭步就抢过去，一伸手，就摘下背后的$w，“玎玎”两声，一剑削出，\n" NOR,
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "金断诀剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "action": "$N" WHT "只觉一股共天地久长的浩气，自心中激游全身，使出覆雨剑法中的"+BLU"「日明诀」"NOR+"，飞袭$n。\n" NOR,
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": HIW"日明诀玄劲" NOR,
        "damage_type": "刺伤"
]),
});

mapping *actionw = ({
([      "action": "$n" HIY "只觉有一股强大的压力，铺天盖地的涌压而来，额上隐然有汗，正是覆雨剑法中的「风流诀」\n" NOR,
        "force" : 550,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 350,
        "weapon": WHT "风流诀玄劲" NOR,
        "damage_type": "内伤"
]),
([      "action": "$n" HIY "刚要刺出，忽然觉得凤涌云动，反被$N一剑自顶至胯，串了进去,   中了"+HIG"「云翳诀」。 \n" NOR,
        "force" : 550,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 350,
        "weapon": WHT "云翳诀剑气" NOR,
        "damage_type": "刺伤"
]),
([      "action": "$N" HIY "卷起手中的$w，面无半点表情，剑光一闪，$w向$n射去。\n" NOR,
        "force" : 550,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 300,
        "weapon": WHT "覆雨破体剑气" NOR,
        "damage_type": "刺伤"
]),

([      "action": "$N" HIY "含笑回转$w" HIY "，左手伸手一指，指天，右手指地，正是天下闻名的"+HIG"「环抱天下」。\n" NOR,
        "force" : 1000,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 500,
        "weapon": WHT "环抱天下无上玄功" NOR,
        "damage_type": "内伤"
]),
});

string main_skill()
{
        return "fuyu-shengong";
}


string *usage_skills = ({"sword", "dodge", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("你对" + to_chinese(usage_skills[i]) + "的理解还"
                                           "不够，无法继续领会更高深的覆雨神功。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("覆雨神功博大精深，无法简单的通过练习进步。\n");
}

int difficult_level()
{
        return 3000;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name1, name2, weapon;
        name1 = xue_name[random(sizeof(xue_name))];
        name2 = attack_name[random(sizeof(attack_name))];

        victim->receive_wound("qi", damage_bonus * 3, me);
        me->add("neili", me->query("jiali") / 3);

        if (victim->query("neili") < 500)
                victim->set("neili", 0);
        else
                victim->add("neili", -300);

        return NOR + HIR "$n" HIR "接下$N" HIR "一招，" + name2 + "顿时破体而"
               "入，全身真气由" + name1 + "狂泻而出。\n" NOR;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        ap = ob->query_skill("parry");
        dp = me->query_skill("fuyu-shengong", 1);

        if (random(ap * 2 / 3) < dp * 3 / 2)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" "以"MAG"「师教诀」之势，竟随在$N之后,"
                                                  "竟让$N产生一种错觉。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" "在这刹那间，身体变得如一根朽木。"
                                                  "在这瞬间将所有的穴道全部闭死.正是"HIM"「木顽诀」。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" "运用"CYN"「水逝诀」在$n周围激起了无数串水柱，"
                                                   "$N的武器全打在水墙上，都无法透过。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" "仗着遥远的火光摇晃，以"RED"「火延诀」之势，"
                                                     "掩人眼目,急闪一旁。\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fuyu-shengong", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fuyu-shengong", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"fuyu-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"fuyu-shengong/exert/" + action;
}


