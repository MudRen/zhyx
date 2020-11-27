//biaotou.c
//��ͷ.c 

inherit NPC;

#include <ansi.h>
void init();
int ask_start();
int ask_arrived();

mapping default_dirs = ([ //root:�ڴ˶����ƶ�����
        "north":                "��",
        "south":                "��",
        "east":                 "��",
        "west":                 "��",
        "northup":              "����",
        "southup":              "�ϱ�",
        "eastup":               "����",
        "westup":               "����",
        "northdown":            "����",
        "southdown":            "�ϱ�",
        "eastdown":             "����",
        "westdown":             "����",
        "northeast":            "����",
        "northwest":            "����",
        "southeast":            "����",
        "southwest":            "����",
        "up":                   "��",
        "down":                 "��",
        "enter":                "��",
        "out":                  "��",
]);

void create()
{
        set("title","��������");
        set_name(HIC "��ͷ" NOR, ({ "biao tou", "tou" }));
        set("nickname",HIW "һ�б���" NOR);
        set("long","����һ���۳ҽ�����ʮ�������ʦ��\n");
        set("gender", "����");
        set("age", 54);
        
        set("food",250);
        set("water",250);

        set("no_get",1);

        set("inquiry", ([
                "����" : (: ask_start :),
                "�ִ�" : (: ask_arrived :),
        ]));
        set("chat_chance_combat", 60);

        setup();

        carry_object(__DIR__"obj/pixue")->wear();
        carry_object(__DIR__"obj/tiejia")->wear();
        carry_object(__DIR__"obj/gangjian")->wield();
}
int accept_hit(object ob)
{
        command("say ë��û����ѧ�˽��ڣ�ȥ���ɣ�");
        command("perform sword.lian");
        kill_ob(ob);
        return 1;
}
int accept_kill(object ob)
{
        command("say ë��û����ѧ�˽��ڣ�ȥ���ɣ�");
        command("yun recover");
        return 1;
}


void init()
{
        add_action("do_move","move");
}

int do_move(string arg)
{
        object me, ob, env;
        mapping exit;
        int busy, kar, i;
        me = this_player();
        ob = this_object();
        env = environment(me);
        kar = 20 + random(10);

        if( !living(ob) )
              return notify_fail("��....����Ȱ�" + ob->name() + "Ū����˵��\n");

        if (ob->query_temp("owner/id") != me->query("id")) {
                command("? " + me->query("id"));
                return notify_fail("\n");
                }
        
        if (!arg) {
                command("kick " + me->query("id"));
                command("whisper "+me->query("id")+" ��Ҫ�Ҹϵ��Ķ�ȥ��");
                return notify_fail("\n");
                }

        if( !mapp(exit = env->query("exits")) || undefinedp(exit[arg]) ) {
                command("?");
                command("whisper "+me->query("id")+" �������û��·����");
                return notify_fail("\n");
                }

        if (ob->is_busy()) {
                command("say �������æ���أ�");
                return notify_fail("\n");
                }

        if (me->is_busy()) {
                command("whisper "+me->query("id")+" ���Լ���æ�������������Ҹ�ʲô��");
                return notify_fail("\n");
                }

        if (ob->is_fighting()) {
                command("whisper "+me->query("id")+" �����Ȱ��ҵĶ��������˰ɣ�\n");
                return notify_fail("\n");
                }

        command("go " + arg); 
        ob->start_busy(2 + random(2));
        me->move(environment(ob));
        message_vision(HIC "��ͷ�þ�����۹�۲������ܡ�\n" NOR,me);
        busy = 2 + random(30 - kar);
        if (busy > 3) busy = 3;
        me->start_busy(busy);
//        i = 30;
//        if ( random(i) < 15){
        ob = new(__DIR__"robber");
        ob->invocation(me);
        
        call_out("robber", 1);

        message_vision(HIR "ͻȻ��һ���ٷ˴Ӱ������˳���������\n\n" NOR,me);

        ob->move(environment(me));
                 
        return 1;
        } 


int ask_start()
{
        object ob = this_object(), me = this_player();

        if (ob->query_temp("started")) {
                command("whisper "+me->query("id")+" �����Ѿ���·������");
                return 1;
                }

        if (me->query("quest/yunbiao") ==1) {
                ob->set_temp("started",1);
                ob->set_temp("owner/id",me->query("id"));
                command("whisper "+me->query("id")+" �ðɣ����ǳ�����");
                return 1;
                }
        
        if (ob->query_temp("owner/id") != me->query("id")) {
                command("slap " + me->query("id"));
                command("whisper "+me->query("id")+" ��û�����㻤�ڣ���Ϲ��ʲô��");
                return 1;
                }
        call_out("leave", 600);
        me->set("task_time", 600);
        return 1;
}

int ask_arrived()
{
        object me, ob;
        int exp, pot, ww, gx, th;
        
        me = this_player();
        ob = this_object();

        if (ob->query_temp("owner/id") != me->query("id")) {
                command("say " + me->query("name") + "�㲢û�л������ڣ�ƾʲô����ȡ������");
                command("grin " + me->query("id"));
                return 1;
                }

        if (ob->is_busy()) {
                command("whisper "+me->query("id")+" �������æ���أ�");
                return notify_fail("\n");
                }

        if (ob->is_fighting()) {
                command("whisper "+me->query("id")+" �����Ȱ��ҵĶ��������˰ɣ�\n");
                return notify_fail("\n");
                }

        if (ob->query_temp("fuzhou") ==1){
                 if (file_name(environment(ob)) !="/d/fuzhou/biaojuzt") {
                         command("whisper "+me->query("id")+" �����;���ϣ�");
                       return 1;
                       }

                if (!present("lin zhennan", environment(ob))) {
                       command("say ����ͷ���ڣ����ý����");
                       return 1;
                       }

   }
   else {
                if (file_name(environment(ob)) !="/d/city/qianzhuang") {
                command("say �����;���ϣ�");
                return 1;
                }

                if (!present("qian yankai", environment(ob))) {
                        command("say Ǯ�ϰ岻�ڣ����ý����");
                        return 1;
                           }
        }
        me->set("quest2/yunbiao",0);
        ww = (100 + random(50));
        gx = (100 + random(50));     
        th = (50 + random(50));               
        exp = (300 + random(30)) * 10;
        pot = (500 + random(exp)) * 2;
        message_vision(HIW "$N�������ˣ�\n"
                + HIG + chinese_number(exp) + "��ʵս���飬\n"  
                + HIC + chinese_number(pot) + "��Ǳ�ܣ�\n"
                + HIR + chinese_number(gx) + "�㹱�ף�\n"
                + HIC + chinese_number(th) + "����ᣬ\n"                
                + HIY + chinese_number(exp * pot / 500000) + "���ƽ�\n" 
                + HIW + chinese_number(ww) + "�㽭��������\n"NOR,me); 

        me->add("combat_exp",exp);
        me->add("potential",pot);
        me->add("gongxian",gx); 
        me->add("experience",th);                
        me->add("balance",(exp * pot/50));
        me->add("weiwang",ww);

        message_vision(CYN "��ʦ��Ǯׯ�����ȥ�ˡ�\n" NOR,me);
        destruct(ob);

        return 1;
}

