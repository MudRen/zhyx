//����2(ת��npc/����ǰ������)

#include <ansi.h>
inherit  NPC;
int ask_recover();
int check_user();
private string *filter_list(string n_special);

//ת��special�б�
mapping re_special = ([ "��Ԫ��" : "recover",
                                                "̫������" : "medicine",
                                                "��������" : "nodie",
                                                "��������" : "jinghua",
                                                "�����ѧ" : "bian",
                                                "��Ȼ����" : "haoran",
                                                "��������" : "ghost",
                                                "����ת��" : "wuxing",
                                                "������ת��" : "wenquxing",
                                          ]);

string *e_special = values(re_special);
string *c_special = keys(re_special);

void create()
{
        seteuid(getuid());       
        set_name(HIY "����Ĳ��" NOR, ({ "buddha", "fo zu", 
                "fo", "shijia muni" }));
        set("long", @LONG
����ׯ�ϱ������˲������ӡ�
LONG);
        set("nickname", HIW "���編��" NOR);
        set("title", HIC "����" NOR);
        set("gender", "����" );
        set("age", 500);
        set("attitude", "friendly");
        set("max_jing", 99999);
        set("max_qi", 99999);
        set("max_jingli", 99999);
        set("jingli", 99999);
        set("max_neili", 99999);
        set("neili", 99999);
        set("jiali", 9999);
        set("str", 99);
        set("int", 99);
        set("con", 99);
        set("dex", 99);
        set("combat_exp", 99999999);

        set("inquiry", ([ 
            "ǰ��" : (: ask_recover :), 
            "ת���ؼ�" : (: check_user :),
        ])); 

        set_skill("dodge", 999);
        set_skill("unarmed", 999);
        set_skill("force", 999);
        set_skill("parry", 999);
        set_skill("sword", 999);      
        set_skill("medical", 999);       
        set_skill("literate", 999);
        set_skill("lamaism", 999);
        set_skill("buddhism", 999);  
        set_skill("shaolin-yishu", 999); 
        set_skill("idle-force", 999);
        set_skill("huntian-baojian", 999);
        set_skill("lunhui-jian", 999);
      
        map_skill("force", "huntian-baojian");       
        map_skill("parry", "lunhui-jian");    
        map_skill("sword", "lunhui-jian");     
        map_skill("medical", "shaolin-yishu");   

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("d/city/obj/jiasha")->wear();
        carry_object("/d/city/obj/changjian")->wield(); 
}





void init()
{
     add_action("do_recall", "recall");
     add_action("do_choose", "choose");
     add_action("do_list", "splist");
     add_action("do_check", "checkme");
     add_action("do_decide", "decide");

}


int ask_recover()
{    
    object me = this_player();

    command("look " + me->query("id"));
    command("say ������ǰ����Ե��?");    
    command("say ��ɼǵ�ǰ����������˭���Ҹ���Ľ�������ʲô��");
    command("say �����ܴ�������ұ���㿪��ǰ��ȫ�����䡣");

    tell_object(me, HIW"�����������˵����"
                    "�����������˾�����recall <id> <����> \n"NOR);   
    return 1;
}

int do_recall(string arg)
{
    int i, have;
    string id, pass;
    mapping special;
    object fo, me = this_player();
    have = 0;   

    if ( me->query("reborn") )
    {
       command("say ��İ���Үʶ�����Ѿ�������");
       return 1;
    }


    fo  = find_object(__DIR__"buddha");  
    if ( ! fo ) fo = load_object(__DIR__"buddha");  

    if ( ! arg || sscanf(arg, "%s %s", id, pass) != 2 )
         return notify_fail("�㾿���ǲ��ǵ��Լ�ǰ����˭��\n");   

    for(i = 0; i < sizeof(fo->query("data")); i++)    
       if (keys(fo->query("data"))[i] == id ) have = 1;

    if ( have == 0 ) 
    {
       command("say ����ô���ǵ�ǰ��������Ե�أ�");
       return 1;
    }

    if ( fo->query("data/" + id + "/reborn_time") 
           > me->query("birthday") ) 
    {
       command("say ����ת��֮ʱ���������ϣ�"
               "������ô���ܻ���������Ͷ̥֮����");
       return 1;
    } 

    if ( fo->query("data/" + id + "/pass") != pass ) 
    {        
       command("say ����������Ҹ���Ľ��");
       return 1;
    }


    command("say �������Ȼ��ǰ��������Ե֮�ˣ����ҽ���ǰ������򿪣�");

    message_vision(HIY"\n����˵�ű㳯��$N����һ���֡�\n\n"NOR
                   HIR"$NͻȻ�е�ͷʹ����......\n\n"NOR, me);

    me->set("str", fo->query("data/" + id + "/str"));
    me->set("int", fo->query("data/" + id + "/int"));
    me->set("con", fo->query("data/" + id + "/con"));
    me->set("dex", fo->query("data/" + id + "/dex"));
   
    if (fo->query("data/" + id + "/sun"))
        me->set("gift/sun",1);
    if (fo->query("data/" + id + "/water"))
        me->set("gift/water",1);
    if (fo->query("data/" + id + "/feng"))
        me->set("gift/feng",1);
    if (fo->query("data/" + id + "/light"))
        me->set("gift/light",1);

    special = fo->query("data/" + id + "/special_skill");
 
    me->delete("special_skill");

    for( i = 0; i < sizeof(special); i++)
       me->set("special_skill/" + values(special)[i], 1); 
     
    me->set("reborn", 1);
    me->set("gift/kaizhan",1);
    me->set("gift/bobo/rmb", 0);
    me->set("gift/jindan",2);

    log_file("static/reborn", sprintf("%s(%s) reborn at %s.\n",
             me->name(1), me->query("id"), ctime(time())));  

    message("vision", HIG"��紫�ž�˵�����ѵ÷�����䣬"
                      "�����˰���Үʶ��\n"NOR, users());
    me->unconcious();

    fo->delete("data/" + id);
    fo->save();   
    return 1;
}

int do_list()
{
        object me =  this_player();
        string msg = HIC"Ŀǰ�ɹ�ѡ���ת���ؼ�Ϊ���£�\n"NOR;
        
        if ( !me->query_temp("can_list"))
                return 0;

        foreach (string skill in e_special)
        {
                     msg += RBSPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
        }
        msg += HIC"��ʹ��ѡ��(choose)ָ�ѡ������Ҫ��һ��special��\n"NOR;
        write(msg);
        me->delete_temp("can_list");
        me->set_temp("can_choose",1);
        return 1;
}
//��ת�� special ����,����Ǹ������ؼ�
int check_user()
{
        object me = this_player();
        //û��ǰ��������
        if (!me->query("reborn") && !wizardp(me))
        {
                command("say �㻹û�г�Ϊת��֮��Ŀǰ���ܸ������⼼�ܡ�");
                return 1;
        }
        //Ҫ��ת���ؼ���
        if (me->query("get_special_ok"))
        {
                command("say ���Ѿ�Ҫ�������ˣ��㲻��̫̰���ˣ������ӷ�");
                return 1;
        }
        //��choose��֧��
        if (me->query_temp("can_list") || me->query_temp("can_choose") || 
                me->query_temp("can_check")     || me->query_temp("can_decide"))
        {
                command("say ��������������ɣ������ӷ�");
                return 1;
        }
        me->set_temp("can_list",1);//����list�ˡ�
        
        tell_object(me, HIC"�����ʹ��splistָ���ѯת���ؼ���,\n"
                                        HIC"�ǵ���ֻ��ѡ��һ����Ȩ��������һ��\n"
                                        HIC"�����Ҵ�����㣬�����ӷ�\n"NOR);
        return 1;
}

//ѡ�� special 
int do_choose(string arg)
{
        object me = this_player();
        string *new_list;
        string msg;
        int x = member_array(arg, c_special);
        int i = 1;//��������
        string new_special1;
        
        if (!me->query_temp("can_choose"))
                return 0;
        
        if ( !arg )
                return notify_fail(HIB"����������Ҫѡ���ת���ؼ����������֣�������splist�쿴�б�\n"NOR);
        
        tell_object(find_player("mike"),arg);
        
        if ( x == -1)
                return notify_fail(HIB"������ļ��ܲ����ڣ�" + x + "������splist�쿴�б�\n"NOR);
        
        new_list = filter_list(arg);//���˺���
        
        //����do����while���ͽ���ѭ������
        do 
        {       
                me->set_temp("rb_special" + i + "/" + e_special[x], 1);
                //���ѡ��һ��
                new_special1 = new_list[random(sizeof(new_list))];
                new_list -= ({ new_special1 });
                me->set_temp("rb_special" + i + "/" + new_special1, 1);
                i++;
        }       while ( i < 4 );
                
                command("say �����ӷ���ļ����Ѿ�ѡ����ϣ�ʹ��checkmeָ����в�ѯ������ϡ�");
                
                me->delete_temp("can_choose");
                me->set_temp("can_check",1);//���Բ�ѯ�ˡ�
                return 1;
}

//���˺���
private string *filter_list(string n_special)
{
        object me = this_player();
        int n_list = member_array(n_special, c_special);
        string now_special = e_special[n_list];
        string *new_sp_list = e_special;
        
        switch (now_special)
        {
                case "wuxing":          new_sp_list -= ({ "wenquxing", "wuxing" });
                                                                                             break;
                case "wenquxing":       new_sp_list -= ({ "wuxing", "wenquxing" });
                                                                                             break;
                default :       new_sp_list -= ({ now_special });
        }
        return new_sp_list;
}
//��ѯ����
int do_check()
{
        object me = this_player();
        
        string msg = HIC"��Ŀǰ�� 3 �鼼�����Ϊ��\n"NOR;
        
        if ( !me->query_temp("can_check"))
                return 0;
        

        for ( int i = 1;i < 4;i++)
                {
                        msg += HBMAG + HIC"���" + i + "��\n"NOR;
                        foreach (string skill in keys(me->query_temp("rb_special" + i + "/")))
                {
                     msg += RBSPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
                }
        }
        msg += HIC"\nʹ�� decide x ָ�����ѡ����ϡ�\n"NOR;
        write(msg);
        
        me->delete_temp("can_check");
        me->set_temp("can_decide",1);
        
        return 1;
}

//����ѡ��x�����
int do_decide(string i)
{
        object me = this_player();
        
        string msg =HIC"���ü������Ϊ" + i + "����ϣ��������£�\n"NOR;
        
        if ( !me->query_temp("can_decide"))
                return 0;
        

        if ( i != "1" && i != "2" && i != "3")
                return notify_fail(HIC"��Ҫ����1��3֮���������\n"NOR);
        
                foreach (string skill in keys(me->query_temp("rb_special" + i + "/")))
        {
                        me->set("rb_special_skill/" + skill, 1); 
                        msg += RBSPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
        }
        write(msg);
        
        me->set("get_special_ok",1);//����
                
        "/cmds/wiz/update.c"->update_player(me);

        return 1;
}

