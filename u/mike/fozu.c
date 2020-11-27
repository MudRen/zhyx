//佛祖2(转世npc/开启前世记忆)

#include <ansi.h>
inherit  NPC;
int ask_recover();
int check_user();
private string *filter_list(string n_special);

//转世special列表
mapping re_special = ([ "破元大法" : "recover",
                                                "太极本草" : "medicine",
                                                "不死金身" : "nodie",
                                                "仙音净化" : "jinghua",
                                                "诡辩奇学" : "bian",
                                                "浩然正气" : "haoran",
                                                "六阴鬼脉" : "ghost",
                                                "武星转世" : "wuxing",
                                                "文曲星转世" : "wenquxing",
                                          ]);

string *e_special = values(re_special);
string *c_special = keys(re_special);

void create()
{
        seteuid(getuid());       
        set_name(HIY "释迦牟尼" NOR, ({ "buddha", "fo zu", 
                "fo", "shijia muni" }));
        set("long", @LONG
佛祖庄严宝像，让人不敢正视。
LONG);
        set("nickname", HIW "三界法王" NOR);
        set("title", HIC "佛祖" NOR);
        set("gender", "男性" );
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
            "前世" : (: ask_recover :), 
            "转世特技" : (: check_user :),
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
    command("say 你与我前世有缘吗?");    
    command("say 你可记得前世你姓甚名谁，我给你的揭语又是什么？");
    command("say 若你能答得上来我便给你开启前生全部记忆。");

    tell_object(me, HIW"佛祖在你耳边说道，"
                    "若你想起来了就输入recall <id> <揭语> \n"NOR);   
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
       command("say 你的阿赖耶识不是已经打开了吗？");
       return 1;
    }


    fo  = find_object(__DIR__"buddha");  
    if ( ! fo ) fo = load_object(__DIR__"buddha");  

    if ( ! arg || sscanf(arg, "%s %s", id, pass) != 2 )
         return notify_fail("你究竟记不记得自己前世是谁？\n");   

    for(i = 0; i < sizeof(fo->query("data")); i++)    
       if (keys(fo->query("data"))[i] == id ) have = 1;

    if ( have == 0 ) 
    {
       command("say 我怎么不记得前世跟你有缘呢？");
       return 1;
    }

    if ( fo->query("data/" + id + "/reborn_time") 
           > me->query("birthday") ) 
    {
       command("say 此人转世之时你已在世上，"
               "你又怎么可能会是他今生投胎之躯？");
       return 1;
    } 

    if ( fo->query("data/" + id + "/pass") != pass ) 
    {        
       command("say 这句哪里是我给你的揭语！");
       return 1;
    }


    command("say 看来你果然是前世与我有缘之人，待我将你前世记忆打开！");

    message_vision(HIY"\n佛祖说着便朝着$N轻轻一挥手。\n\n"NOR
                   HIR"$N突然感到头痛欲裂......\n\n"NOR, me);

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

    message("vision", HIG"天界传闻据说有人已得佛祖恩典，"
                      "开启了阿赖耶识。\n"NOR, users());
    me->unconcious();

    fo->delete("data/" + id);
    fo->save();   
    return 1;
}

int do_list()
{
        object me =  this_player();
        string msg = HIC"目前可供选择的转世特技为如下：\n"NOR;
        
        if ( !me->query_temp("can_list"))
                return 0;

        foreach (string skill in e_special)
        {
                     msg += RBSPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
        }
        msg += HIC"请使用选择(choose)指令，选择你需要的一个special。\n"NOR;
        write(msg);
        me->delete_temp("can_list");
        me->set_temp("can_choose",1);
        return 1;
}
//给转世 special 函数,设计是给两个特技
int check_user()
{
        object me = this_player();
        //没打开前世记忆呢
        if (!me->query("reborn") && !wizardp(me))
        {
                command("say 你还没有成为转世之身，目前不能给你特殊技能。");
                return 1;
        }
        //要完转世特技了
        if (me->query("get_special_ok"))
        {
                command("say 你已经要过技能了，你不能太贪心了，阿弥陀佛。");
                return 1;
        }
        //在choose分支呢
        if (me->query_temp("can_list") || me->query_temp("can_choose") || 
                me->query_temp("can_check")     || me->query_temp("can_decide"))
        {
                command("say 你现在有事在身吧，阿弥陀佛。");
                return 1;
        }
        me->set_temp("can_list",1);//可以list了。
        
        tell_object(me, HIC"你可以使用splist指令查询转世特技了,\n"
                                        HIC"记得你只有选择一个的权利，另外一个\n"
                                        HIC"将由我赐予给你，阿弥陀佛。\n"NOR);
        return 1;
}

//选择 special 
int do_choose(string arg)
{
        object me = this_player();
        string *new_list;
        string msg;
        int x = member_array(arg, c_special);
        int i = 1;//计数变量
        string new_special1;
        
        if (!me->query_temp("can_choose"))
                return 0;
        
        if ( !arg )
                return notify_fail(HIB"请输入你需要选择的转世特技的中文名字，请输入splist察看列表。\n"NOR);
        
        tell_object(find_player("mike"),arg);
        
        if ( x == -1)
                return notify_fail(HIB"你输入的技能不存在，" + x + "请输入splist察看列表。\n"NOR);
        
        new_list = filter_list(arg);//过滤函数
        
        //采用do……while句型进行循环控制
        do 
        {       
                me->set_temp("rb_special" + i + "/" + e_special[x], 1);
                //随机选择一个
                new_special1 = new_list[random(sizeof(new_list))];
                new_list -= ({ new_special1 });
                me->set_temp("rb_special" + i + "/" + new_special1, 1);
                i++;
        }       while ( i < 4 );
                
                command("say 阿弥陀佛，你的技能已经选择完毕，使用checkme指令进行查询技能组合。");
                
                me->delete_temp("can_choose");
                me->set_temp("can_check",1);//可以查询了。
                return 1;
}

//过滤函数
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
//查询函数
int do_check()
{
        object me = this_player();
        
        string msg = HIC"你目前的 3 组技能组合为：\n"NOR;
        
        if ( !me->query_temp("can_check"))
                return 0;
        

        for ( int i = 1;i < 4;i++)
                {
                        msg += HBMAG + HIC"组合" + i + "：\n"NOR;
                        foreach (string skill in keys(me->query_temp("rb_special" + i + "/")))
                {
                     msg += RBSPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
                }
        }
        msg += HIC"\n使用 decide x 指令，进行选择组合。\n"NOR;
        write(msg);
        
        me->delete_temp("can_check");
        me->set_temp("can_decide",1);
        
        return 1;
}

//决定选择x号组合
int do_decide(string i)
{
        object me = this_player();
        
        string msg =HIC"你获得技能组合为" + i + "号组合，技能如下：\n"NOR;
        
        if ( !me->query_temp("can_decide"))
                return 0;
        

        if ( i != "1" && i != "2" && i != "3")
                return notify_fail(HIC"你要输入1和3之间的整数。\n"NOR);
        
                foreach (string skill in keys(me->query_temp("rb_special" + i + "/")))
        {
                        me->set("rb_special_skill/" + skill, 1); 
                        msg += RBSPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
        }
        write(msg);
        
        me->set("get_special_ok",1);//结束
                
        "/cmds/wiz/update.c"->update_player(me);

        return 1;
}

