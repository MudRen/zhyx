// Updated by Lonely

#include <ansi.h>
inherit NPC;

mapping *first_name=({
([      "name":"��",      "id":"sun"    ]),
([      "name":"��",      "id":"wu"     ]),
([      "name":"����",    "id":"dugu"   ]),
([      "name":"��",      "id":"lai"    ]),
([      "name":"��",      "id":"lin"    ]),
([      "name":"��",      "id":"zhao"   ]),
([      "name":"��",      "id":"ren"    ]),
([      "name":"Ǯ",      "id":"qian"   ]),
([      "name":"��",      "id":"li"     ]),
([      "name":"��",      "id":"zhang"  ]),
([      "name":"�",      "id":"zang"   ]),
([      "name":"��",      "id":"xu"     ]),
([      "name":"��",      "id":"yang"   ]),
([      "name":"��",      "id":"qiu"    ]),
([      "name":"��",      "id":"shu"    ]),
([      "name":"Ҷ",      "id":"ye"     ]),
([      "name":"��",      "id":"liu"    ]),
([      "name":"��",      "id":"zhou"   ]),
([      "name":"��",      "id":"yang"   ]),
([      "name":"��",      "id":"wang"   ]),
([      "name":"��",      "id":"liang"  ]),
([      "name":"��",      "id":"huang"  ]),
([      "name":"��",      "id":"lin"    ]),
([      "name":"��",      "id":"chen"   ]),
([      "name":"л",      "id":"xie"    ]),
([      "name":"³",      "id":"lu"     ]),
([      "name":"��",      "id":"he"     ]),
([      "name":"��",      "id":"zeng"   ]),
([      "name":"��",      "id":"guo"    ]),
([      "name":"��",      "id":"cheng"  ]),
([      "name":"�Ϲ�",    "id":"nangong"  ]),
([      "name":"ŷ��",    "id":"ouyang"   ]),
([      "name":"����",    "id":"zhangsun" ]),
([      "name":"Ľ��",    "id":"murong"   ]),
([      "name":"����",    "id":"ximen"    ]),
([      "name":"����",    "id":"gongsun"  ]),
([      "name":"��ľ",    "id":"duanmu"  ]),
});

mapping *second_name=({
([      "name":"",      "id":""      ]),
([      "name":"��",    "id":"feng"  ]),
([      "name":"��",    "id":"de"    ]),
([      "name":"��",    "id":"xiao"  ]),
([      "name":"��",    "id":"fu"    ]),
([      "name":"��",    "id":"da"    ]),
([      "name":"Ĭ",    "id":"mo"    ]),
([      "name":"��",    "id":"xuan"  ]),
([      "name":"��",    "id":"hai"   ]),
([      "name":"��",    "id":"zi"    ]),
([      "name":"̩",    "id":"tai"   ]),
([      "name":"��",    "id":"zhao"  ]),
([      "name":"",      "id":""      ]),
([      "name":"ͨ",    "id":"tong"  ]),
([      "name":"��",    "id":"yun"   ]),
([      "name":"��",    "id":"fen"   ]),
([      "name":"��",    "id":"hong"  ]),
([      "name":"��",    "id":"rong"  ]),
([      "name":"��",    "id":"peng"  ]),
([      "name":"��",    "id":"chong" ]),
([      "name":"�",    "id":"hao"   ]),
([      "name":"˼",    "id":"si"    ]),
([      "name":"��",    "id":"li"    ]),
([      "name":"��",    "id":"gang"  ]),
([      "name":"��",    "id":"wu"    ]),
([      "name":"��",    "id":"yi"    ]),
});
          
mapping *third_name=({
([      "name":"��",    "id":"feng"  ]),
([      "name":"��",    "id":"hua"   ]),
([      "name":"��",    "id":"qi"    ]),
([      "name":"��",    "id":"ge"    ]),
([      "name":"��",    "id":"xu"    ]),
([      "name":"��",    "id":"fa"    ]),
([      "name":"��",    "id":"wei"   ]),
([      "name":"��",    "id":"hui"   ]),
([      "name":"��",    "id":"cheng" ]),
([      "name":"��",    "id":"xuan"  ]),
([      "name":"��",    "id":"yong"  ]),
([      "name":"̩",    "id":"tai"   ]),
([      "name":"��",    "id":"zai"   ]),
([      "name":"��",    "id":"jun"   ]),
([      "name":"��",    "id":"jun"   ]),
([      "name":"��",    "id":"fan"   ]),
([      "name":"ΰ",    "id":"wei"   ]),
([      "name":"��",    "id":"fan"   ]),
([      "name":"��",    "id":"xiong" ]),
([      "name":"��",    "id":"tao"   ]),
([      "name":"��",    "id":"bo"    ]),
([      "name":"��",    "id":"jie"   ]),
([      "name":"��",    "id":"lang"  ]),
});                                     

string *degree_desc=({
       HIC "�Խ�" NOR,
       HIY "����" NOR,
       HIY "����" NOR,
       HIR "����" NOR,
       HIR "�ᶽ" NOR,
       HIR "�ܶ�" NOR,
       MAG "��������" NOR,
       MAG "��������" NOR,
       HIB "�򱱽ڶ�ʹ" NOR,
});                            

int get_exp_rate();
int get_level(int exp);   

// �����η���
int sqrt3(int x) 
{
        float y = 1.0 / 3.0; 
        x = pow(x, y); 
        return x; 
}

void create()
{
        int lvl, skill, nl, exp;
        string id, idf;
        string name;  
        int index;

        index = random(sizeof(first_name));
        name = first_name[index]["name"];
        id = first_name[index]["id"];
        idf = id; 

        index = random(sizeof(second_name));
        name += second_name[index]["name"];
        id += " " + second_name[index]["id"];

        index = random(sizeof(third_name));
        name += third_name[index]["name"];
        id += third_name[index]["id"];

        set_name(name, ({id, idf}));

        set("gender", "����");
        set("age", random(20) + 20);
        set("str", 160);
        set("dex", 160);
        set("con", 160);

        set("long", "����һ�����ν��������������ݵ�Ѳ�����Լ��Ķ��顣\n");

        set("int", 30);
        set("str", 30 + random(20));
        set("con", 20 + random(20));
        set("dex", 20 + random(20));
        set("age", 20 + random(30));
        set("per", 15 + random(15)); 
        set("age", 20 + random(30));
        set("per", 15 + random(15));                                         
        set("no_get",1);
        
        exp = get_exp_rate() / 10;
        skill = get_level(exp);
        
        if (skill < 100) skill = 100;
        
        set("combat_exp", exp);       
        nl = skill * 10 + exp / 10000;
        
        set("max_neili", nl);
        set("neili", query("max_neili") * 3 / 2); 
        set("max_jingli", nl);
        set("jingli", query("max_jingli"));
        set("max_qi", nl * 10);
        set("qi",  query("max_qi"));
        set("eff_qi", query("max_qi"));
        set("max_jing", nl);
        set("eff_jing", query("max_jing"));
        set("jiali", skill / 2); 

        set_skill("taiji-shengong", skill);
        set_skill("wuhu-duanmendao", skill);
        set_skill("tiyunzong", skill);
        set_skill("taiji-quan", skill);
        set_skill("cuff", skill);
        set_skill("force", skill);
        set_skill("dodge", skill);
        set_skill("blade", skill);
        set_skill("parry", skill);
        set_skill("arrow", skill*2/3);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("blade", "wuhu-duanmendao");   
        prepare_skill("cuff", "taiji-quan");
  
        set_temp("jun_quest/party", "song"); 
        set("quest_ob", 1);  
        set("start_time", time());
        add_temp("apply/armor", 400);
        add_temp("apply/damage", 100);
        setup();
        
        lvl = (query("str") + skill / 10) / 10 - 1;
        if (lvl > 8) lvl = 8;
        lvl = lvl - 2;
        if (lvl < 3) lvl = 3;
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl);
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl);
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl);
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl);
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/tiejia")->wear();   
        carry_object(__DIR__"obj/pifeng")->wear();  
}

int get_level(int exp)
{
        int level;
        
        exp /= 1000;
        level = sqrt3(exp);
        return level * 10;
}

int get_exp_rate()
{
        int max_exp = 10000000, exp_rate;
        
        foreach (object user in users())
        {
                if (! environment(user)) continue;
                if (wizardp(user)) continue;
                
                if (user->query("combat_exp") > max_exp)
                        max_exp = (int)user->query("combat_exp");
        }

        return max_exp;
}

void change_ob()
{ 
        int jungong;
        object ling, king;

        jungong = 4 + random(query("combat_exp") / 5000000 + 1);
        if (jungong > 12) jungong = 12;
        set("title", degree_desc[jungong - 4]);
        set("degree_jungong", jungong);
        
        king = WAR_D->query_king();
        
        ling = new("/adm/npc/obj/lingjian");
        ling->set("owner", query("id"));
        
        if (objectp(king))
                ling->set("master", king->query("id"));
                
        ling->move(this_object());
        ling->check_me(this_object());
        return;
}

void init()
{     
        if (this_player()->query_temp("jun_quest/party") != "meng")
        {
                add_action("do_kill", "team kill");
                add_action("do_kill", "touxi");
                add_action("do_kill", "kill");
                add_action("do_kill", "hit");
                add_action("do_kill", "fight");
                add_action("do_kill", "steal");
                add_action("do_kill", "beg");
                add_action("do_kill", "persuade");
        }                    
}       

int do_kill(string arg)
{
        string what, who;
        
        if (! arg) return 0;
                               
        if (this_object()->id(arg))
        {
                write("��û�и�����Ǿ���Ү���������ܣ���\n");
                return 1;
        }
        else
        if (sscanf(arg,"%s from %s", what, who) == 2 && this_object()->id(who))
        {
                write("��û�и�����Ǿ���Ү���������ܣ���\n");
                return 1;
        }
        return 0;
}

void die()
{
        message_vision("$N������ξ���ʿ�Ѳ����ڣ�����"
                + HIR "ȫ����û" NOR "��\n", this_object());
        destruct(this_object());
        return;
}

