// 山猫(adx) by snow 2000-05-15

//inherit F_MASTER;
//inherit F_UNIQUE;
inherit NPC;
inherit F_SAVE;

#include <ansi.h>

string status_color(string current, string str);
string delcolor(string str2);
int fenzu(string *inv);
int xuanbu();
int huihe();
int start_biwu();
int keep_biwu(string id);
int end_biwu();
int jieshu_biwu(string id1, string id2);

#ifndef NPCDATA
#define NPCDATA "/d/biwu/npc/"
#endif
#define GONGPING NPCDATA + "gongping"

#define WIZLEVEL        5
#define TIME            60

#define BIWUA   "个人赛"
#define BIWUB   "擂台赛"
#define BIWUC   "门派赛"
#define BIWUD   "循环赛"

string query_save_file()
{
        return GONGPING;
}

int save()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file+ __SAVE_EXTENSION__);
//              return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) )
//              return restore_object(file);
        return 0;
}

void create()
{
        seteuid(getuid());

        if (!restore()) {
        set_name("公平子", ({ "gongping zi", "gongping", "zi" }) );
        set("title", HIW"四海散人"NOR);
        set("long",
                "这是一位仙风道骨的中年道人，早年云游四方，性好任侠，公正无私。\n");
        set("gender", "男性" );
        set("age", 40);
        set("biwudahui",1);
        set("no_clean_up",1);

        setup();
        carry_object("/clone/misc/cloth")->wear();        
        }
        else {
                set("id", "gongping zi");
                set_name(query("name"), ({  "gongping zi", "gongping", "zi" }));
        setup();      
        }
}

void init()
{
        object me = this_player();

        add_action("do_canjia", "canjia");
        add_action("do_menpai", "menpai");
        add_action("do_list", "chaxun");

        if (wizardp(me) && wiz_level(me) >= WIZLEVEL) {
                add_action("do_start", "start");
                add_action("do_biwu", "biwu");
                add_action("do_agree", "agree");
                add_action("do_diss", "dissent");
                add_action("do_del", "del");
        }
}

int do_start(string arg)
{
        object ob=this_object();
        int i=ob->query("biwudahui");
        int a;
        string *inv, *str, *menpai;

        if(!arg)
                return notify_fail("你要开始哪项比武？\n");

        if(ob->query("start/start"))
                return notify_fail("比武大会已经开始了。\n");

        if(arg=="xunhuan") {
		if (! ob->query("biwu_baoming"))
			return notify_fail("还没有人报名，比武大会无法开始。\n");

                inv=keys(ob->query("biwu_baoming"));
                if(sizeof(inv)<4)
                        return notify_fail("报名的人太少了，比武大会无法开始。\n");
                message("channel:chat",HIW"【比武场】第"+CHINESE_D->chinese_number(i)+
                        "届比武大会一分钟后开始！请所有已报名选手速到比武场来！\n"NOR,users());
                ob->set("start/start", arg);
                fenzu(inv);
                return 1;
        }

	if (! ob->query("menpai_baoming"))
		return notify_fail("门派比赛还没有人报名，无法开始。\n");

        str=keys(ob->query("menpai_baoming"));
        for(a=0; a<sizeof(str); a++) {
                if(arg==str[a]) {
                        if(ob->query("fangshi")!=BIWUC)
                                return notify_fail("你必须先将比武方式切换为门派赛。\n");
                        menpai=keys(ob->query("menpai_baoming/"+arg));
                        if(sizeof(menpai)<4)
                                return notify_fail("报名的人太少了，比武大会无法开始。\n");
                        message("channel:chat",HIW"【比武场】"HIM+arg+HIW"掌门大弟子选拔"+
                        "比武一分钟后开始！请所有已报名选手速到比武场来！\n"NOR,users());
                        ob->set("start/start", arg);
                        fenzu(menpai);
                        return 1;
                }
        }
        return notify_fail("这个门派还未提出申请！\n");
}

int fenzu(string *inv)
{
        object ob=this_object();
        string id1, id2, id3, id4, id;
        mapping fenzu, str;
        int a=1;
        int b=1;
        int i, j, k;

        ob->delete("huihe");
        ob->delete("fenzu");
        ob->delete("jifen");
        ob->add("start/lunxu", 1);
        ob->set("start/huihe", 1);
        ob->set("start/cxu", 1);
        for(i=0; i<sizeof(inv); i++) {
                id=inv[i];
                if(find_player(id)) {
                        ob->set("fenzu/"+a+"/"+b, id);
                        b=b+1;
                }
                if(b>4) { b=1; a=a+1; }
        }
        
        fenzu=ob->query("fenzu");
        for(i=1; i<(sizeof(fenzu)+1); i++) {
                str=ob->query("fenzu/"+i);
                for(j=1; j<(sizeof(str)+1); j++) {
                        id=ob->query("fenzu/"+i+"/"+j);
                        if(j==1) id1=id;
                        if(j==2) id2=id;
                        if(j==3) id3=id;
                        if(j==4) id4=id;
                }
                if((sizeof(str))==4) {
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id1);
                        ob->set("huihe/"+k+"/ob2", id2);
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id3);
                        ob->set("huihe/"+k+"/ob2", id4);
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id1);
                        ob->set("huihe/"+k+"/ob2", id3);
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id2);
                        ob->set("huihe/"+k+"/ob2", id4);
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id1);
                        ob->set("huihe/"+k+"/ob2", id4);
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id2);
                        ob->set("huihe/"+k+"/ob2", id3);
                }
                if((sizeof(str))==3) {
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id1);
                        ob->set("huihe/"+k+"/ob2", id2);
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id2);
                        ob->set("huihe/"+k+"/ob2", id3);
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id1);
                        ob->set("huihe/"+k+"/ob2", id3);
                }
                if((sizeof(str))==2) {
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id1);
                        ob->set("huihe/"+k+"/ob2", id2);
                }
                if((sizeof(str))==1) {
                        k=k+1;
                        ob->set("huihe/"+k+"/ob1", id1);
                }
        }
        ob->delete("chuxian");
        save();
        xuanbu();
        return 1;
}

int xuanbu()
{
        object ob=this_object();
        int j=ob->query("start/lunxu");
        string *menpai=ob->query("fenzu");
        string *str, id, msg;
        int a, b;

        message("channel:chat",HIW"【比武场】公平子朗声宣布道：第"+
                CHINESE_D->chinese_number(j)+"轮比武分组如下：\n",users());

        for(a=1; a<(sizeof(menpai)+1); a++) {
                msg=HIW"第"+CHINESE_D->chinese_number(a)+"组：";
                str=ob->query("fenzu/"+a+"/");
                for(b=1; b<(sizeof(str)+1); b++) {
                        id=ob->query("fenzu/"+a+"/"+b+"");
                        msg+=""+find_player(id)->query("name")+"("+id+")\t";
                }
                message("channel:chat",HIW""+msg+"\n",users());
        }
        remove_call_out("start_biwu");
        call_out("start_biwu", TIME);
        return 1;
}

int start_biwu()
{
        object ob=this_object();
        int i=ob->query("start/lunxu");
        int j=ob->query("start/huihe");
        string id1, id2;
        string *str=keys(ob->query("huihe"));
        object ob1, ob2;

        ob->add("start/huihe", 1);
        ob->add("start/cxu", 1);

        if((sizeof(str))==1) {
                ob->delete("start/lunxu");
                ob->delete("start/huihe");
                ob->delete("start/cxu");
                end_biwu();
                return 1;
        }

        if( (sizeof(ob->query("huihe/"+j)))==1 ) {
                id1=ob->query("huihe/"+j+"/ob1");
                keep_biwu(id1);
        }

        id1=ob->query("huihe/"+j+"/ob1");
        id2=ob->query("huihe/"+j+"/ob2");
        ob1=find_player(id1);
        ob2=find_player(id2);

        if(!ob1 && !ob2) {
                message("channel:chat",HIW"【比武场】公平子宣布道：第"+
                        CHINESE_D->chinese_number(i)+"轮，第"+
                        CHINESE_D->chinese_number(j)+"回合比武：\n"+
                        "                由于"+"("+id1+")与("+id2+")"+
                        "均缺阵！本回合取消！继续下一轮！\n",users());
                remove_call_out("start_biwu");
                call_out("start_biwu", 2);
        }
        if(!ob1) {
                message("channel:chat",HIW"【比武场】公平子宣布道：第"+
                        CHINESE_D->chinese_number(i)+"轮，第"+
                        CHINESE_D->chinese_number(j)+"回合比武：\n"+
                        "                由于("+id1+")缺阵！"+ob2->query("name")+"("+id2+")"+
                        "胜出！\n",users());
                keep_biwu(id2);
        }
        if(!ob2) {
                message("channel:chat",HIW"【比武场】公平子宣布道：第"+
                        CHINESE_D->chinese_number(i)+"轮，第"+
                        CHINESE_D->chinese_number(j)+"回合比武：\n"+
                        "                由于("+id2+")缺阵！"+ob1->query("name")+"("+id1+")"+
                        "胜出！\n",users());
                keep_biwu(id1);
        }

        message("channel:chat",HIW"【比武场】公平子宣布道：第"+
                CHINESE_D->chinese_number(i)+"轮，第"+
                CHINESE_D->chinese_number(j)+"回合比武：\n"NOR+YEL+
                "                "BLINK+
                ob1->query("name")+"("+id1+")"+"---V.S.---"+
                ob2->query("name")+"("+id2+")\n"NOR,users());
        ob->set("start/biwu_fighter1", id1);
        ob->set("start/biwu_fighter2", id2);
        ob1->set("biwu_fighter", 1);
        ob2->set("biwu_fighter", 1);
        return 1;
}

int keep_biwu(string id)
{
        object ob=this_object();
        string *str=keys(ob->query("huihe"));
        string *inv, *str1, *str2, id1, *fenzu;
        int k=ob->query("start/cxu");
        int i, j;

        if(id=="adx") {
                k=k+1;
        } else {
                ob->add("jifen/"+id, 1);
        }
        if(k>sizeof(str)) {
                ob->delete("jifen/0");
                ob->delete("start/cxu");
                str1=keys(ob->query("fenzu"));

                for(i=1; i<(sizeof(str1)+1); i++) {
                        fenzu=keys(ob->query("fenzu/"+i));

                        if(sizeof(fenzu)>=3) {
                                for(j=1; j<(sizeof(fenzu)+1); j++) {
                                        id1=ob->query("fenzu/"+i+"/"+j);
                                        if(ob->query("jifen/"+id1)>=2)
                                                ob->set("chuxian/"+id1, 1);
                                }
                        }
                        if(sizeof(fenzu)==2) {
                                for(j=1; j<(sizeof(fenzu)+1); j++) {
                                        id1=ob->query("fenzu/"+i+"/"+j);
                                        if(ob->query("jifen/"+id1)>=1)
                                                ob->set("chuxian/"+id1, 1);
                                }
                        }
                        if(sizeof(fenzu)==1) {
                                id1=ob->query("fenzu/"+i+"/1");
                                ob->set("chuxian/"+id1, 1);
                        }
                }
                inv=keys(ob->query("chuxian"));
                fenzu(inv);
                return 1;
        }

        remove_call_out("start_biwu");
        call_out("start_biwu", 2);
}

int end_biwu()
{
        object ob=this_object();
        int i=ob->query("biwudahui");
        string *id=keys(ob->query("huihe/1/"));
        string id1, id2;
        object ob1, ob2;

        if(id1=ob->query("huihe/1/ob1")) ob1=find_player(id1);
        if(id2=ob->query("huihe/1/ob2")) ob2=find_player(id2);

        if(sizeof(id)==1) {
                message("channel:chat",HIW"【比武场】公平子朗声宣布道：由于第"+
                        CHINESE_D->chinese_number(i)+"届比武大会最后一轮\n"+
                        "        只有"+ob1->query("name")+"("+id1+")"+
                        "出线，所以比武到此结束！\n"NOR,users());
                jieshu_biwu(id1, id2);
                return 1;
        }
        ob->set("start/juesai", 1);
        message("channel:chat",HIW"【比武场】公平子朗声宣布道：现在到了第"+
                CHINESE_D->chinese_number(i)+"届比武大会决赛的时候了：\n",users());
        message("channel:chat",HIW"【比武场】公平子宣布道，决赛由：\n"NOR+YEL+
                "                "BLINK+
                ob1->query("name")+"("+id1+")"+"---V.S.---"+
                ob2->query("name")+"("+id2+")\n"NOR,users());
        ob->set("start/biwu_fighter1", id1);
        ob->set("start/biwu_fighter2", id2);
        ob1->set("biwu_fighter", 1);
        ob2->set("biwu_fighter", 1);
        return 1;
}

int jieshu_biwu(string id1, string id2)
{
        object ob=this_object();
        object ob1, ob2;
        string str=ob->query("start/start");
        string msg;
        int i=ob->query("biwudahui");

        if(id1) ob1=find_player(id1);
        if(id2) ob2=find_player(id2);

        if(str=="xunhuan") {
                if(!ob2) {
                        message("channel:chat",HIY"                "+
                                "冠军是："BLINK+ob1->query("name")+"("+id1+")"+
                                "\n"NOR,users());
                        msg=""+ob1->query("name")+"("+id1+")";
                        ob->set("biwu_jieguo/"+i+"/1", msg);
                } else {
                         message("channel:chat",HIW"【比武场】公平子朗声宣布道：第"+
                                CHINESE_D->chinese_number(i)+
                                "届比武大会到此结束！\n",users());
                        message("channel:chat",HIY"                "+
                                "冠军是："BLINK+ob1->query("name")+"("+id1+")"+
                                "\n"NOR,users());
                        message("channel:chat",WHT"                "+
                                "亚军是："BLINK+ob2->query("name")+"("+id2+")"+
                                "\n"NOR,users());
                        msg=""+ob1->query("name")+"("+id1+")";
                        ob->set("biwu_jieguo/"+i+"/1", msg);
                        msg=""+ob1->query("name")+"("+id2+")";
                        ob->set("biwu_jieguo/"+i+"/2", msg);
                }
                ob->add("biwudahui", 1);
                ob1->set("snowzongshi",1);
                ob->delete("biwu_baoming");
        } else {
                if(!ob2) {
                        message("channel:chat",HIR"        祝贺"+
                                BLINK+ob1->query("name")+"("+id1+")"+
                                "荣任"+str+"掌门大弟子！\n"NOR,users());
                } else {
                        message("channel:chat",HIW"【比武场】公平子朗声宣布道："+
                                str+"掌门大弟子选拔比武到此结束！\n",users());
                        message("channel:chat",HIR"        祝贺"+
                                BLINK+ob1->query("name")+"("+id1+")"+
                                "荣任"+str+"掌门大弟子！\n"NOR,users());
                }
                ob->set("biwu_jieguo/"+str,""+ob1->query("name")+"("+id1+")"+"");
                ob->delete("menpai_baoming/"+str);
                msg=HIY""+str+"掌门大弟子"NOR;
                ob1->set("title", msg);
                ob->delete("menpai/"+str+"");
        }
        ob->delete("start");
        ob->delete("jifen");
        ob->delete("huihe");
        ob->delete("fenzu");
        save();
        return 1;
}

int do_list(string arg)
{
        object ob=this_object();
        string *menpai, name, long, *inv, family;
        mapping site;
        int a;

        if(!arg) {
                message_vision(CYN"查询比武大会报名情况 用(chaxun 参加)\n"NOR, ob);
                message_vision(CYN"查询门派申请比武情况 用(chaxun 申请)\n"NOR, ob);
                message_vision(CYN"查询门派比武报名情况 用(chaxun <门派中文名>)\n"NOR, ob);
                return 1;
        }
        if(arg=="申请") {
                if(!ob->query("menpai") || sizeof(ob->query("menpai"))<1)
                        return notify_fail("现在比武大会还没有开始接受报名！\n");

                printf(HIB"\n┏━"+HBWHT RED"各门派掌门大弟子比武大会申请表"NOR+
                        HIB"━━━━━━━━━━━━┓\n"NOR);
                printf(HIB"┃ 门派名称 ┃  申   请   者  ┃  巫  师  审   核  情  况 ┃\n"NOR);
                printf(HIB"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"NOR);

                menpai=keys(ob->query("menpai"));
                for(a=0; a<sizeof(menpai); a++) {
                        family=menpai[a];
                        site=ob->query("menpai/"+family);
                        name=site["name"];
                        long=site["long"];
                printf(HIB"┃"NOR+"%10s"+HIB"┃"NOR+"%16s"+HIB"┃"NOR+"%26s"+HIB"┃\n"NOR,
                        family, name, long);
                }

                printf(HIB"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"NOR);
                return 1;
        }

        if(arg=="参加") {
		if(ob->query("fangshi") != BIWUD)
			return notify_fail("现在不是举办比武大会的时候！\n");

		if(!ob->query("biwu_baoming"))
			return notify_fail("目前还没有人报名参赛！\n");

                inv=keys(ob->query("biwu_baoming"));
                printf(CYN"公平子道：以下是已经报名参加本届比武大会的名单。\n");
                for(a=0; a<sizeof(inv); a++) {
                        site=ob->query("biwu_baoming/"+inv[a]+"/");
                        printf("%s(%s)\t", site["name"], site["id"]);
                        if((a+1)%3 == 0 )
                                printf("\n");
                }
                printf("\n"NOR);
                return 1;
        }

	if (! ob->query("menpai_baoming"))
		return notify_fail("目前该门派还没有申请大弟子选拔比武！\n");
		
        menpai=keys(ob->query("menpai_baoming"));

        if(!ob->query("menpai/"+arg+"/agree"))
                return notify_fail("巫师还未批准"+arg+"举办掌门大弟子选拔比武！\n");
        for(a=0; a<sizeof(menpai); a++) {
                if(menpai[a]==arg) {
                        inv=keys(ob->query("menpai_baoming/"+arg+"/"));
                printf(CYN"公平子道：以下是已经报名参加"+arg+"掌门大弟子选拔比武的名单。\n");
                        for(a=0; a<sizeof(inv); a++) {
                                site=ob->query("menpai_baoming/"+arg+"/"+inv[a]);
                                printf("%s(%s)\t", site["name"], site["id"]);
                                if((a+1)%3==0)
                                        printf("\n");
                        }
                printf("\n"NOR);
                return 1;
                }
        }
        return notify_fail(""+arg+"还没有人报名参加掌门大弟子比武！\n");
}

int do_canjia()
{
        object me=this_player();
        object ob=this_object();
        int i=ob->query("biwudahui");
        string str=ob->query("fangshi");
        string id=me->query("id");
        string name=me->query("name");
        string family=me->query("family/family_name");

        if(wizardp(me))
                return notify_fail("巫师也要参加比武？？\n");

        if(me->query("age")<=16)
                return notify_fail("未满十六岁的不能参加比武！\n");

        if(ob->query("start/start"))
                return notify_fail("比武已经开始了，现在不接受报名！\n");

        if(!family) family="无门派";
                family=delcolor(family);

        if(str==BIWUD) {
                message_vision(CYN"$N向$n报名参加第"+CHINESE_D->chinese_number(i)+
                        "届比武大会！\n"NOR, me, ob);

                if(ob->query("biwu_baoming/"+id+"/id")==id) {
                        message_vision(CYN"$n对$N道：你已经报过名参加本届比武啦！\n"NOR, me, ob);
                        return 1;
                }

                ob->set("biwu_baoming/"+id+"/id", id);
                ob->set("biwu_baoming/"+id+"/name", name);
                ob->set("biwu_baoming/"+id+"/family", family);

                message_vision(CYN"$n掏出本子把$N的名字记了下来。\n"NOR, me, ob);
                save();
                return 1;
        }

//      if(str==BIWUC) {
                message_vision(CYN"$N向$n报名参加"+family+"掌门大弟子选拔比武！\n"NOR, me, ob);
                if(ob->query("menpai/"+family+"/family")==family) {
                        if(!ob->query("menpai/"+family+"/agree")) {
                        message_vision(CYN"$n对$N道：贵派的比武申请巫师还未批准！\n"NOR, me, ob);
                                return 1;
                        }

                        if(ob->query("menpai_baoming/"+family+"/"+id+"/id")==id) {
                        message_vision(CYN"$n对$N道：你已经报过名参加贵派的比武啦！\n"NOR,me,ob);
                                return 1;
                        }
                        ob->set("menpai_baoming/"+family+"/"+id+"/id", id);
                        ob->set("menpai_baoming/"+family+"/"+id+"/name", name);
                        message_vision(CYN"$n对$N道：好我记下了！\n"NOR, me, ob);
                        save();
                        return 1;
                }
        message_vision(CYN"$n对$N道：贵派还未提出举办掌门大弟子选拔的比武申请！\n"NOR, me, ob);
        return 1;
//      }
}

int do_menpai()
{
        object me=this_player();
        object ob=this_object();
        string id=me->query("id");
        string name=me->query("name");
        string family=me->query("family/family_name");

        if(wizardp(me))
                return notify_fail("巫师也要组织比武？？\n");

        if(!family)
                return notify_fail("你还未加入任何门派！\n");
                family=delcolor(family);

        if(me->query("combat_exp")<100000)
                return notify_fail("你的武功太差了，不能提出申请！\n");

        if(ob->query("start/start"))
                return notify_fail("比武已经开始了，现在不接受申请！\n");

//      if(ob->query("fangshi")!=BIWUC)
//              return notify_fail("现在不是门派举办掌门大弟子比武选拔大会的时候！\n");

        message_vision(CYN"$N对$n道："+family+
                "要求举办掌门大弟子比武选拔大会！\n"NOR, me, ob);

        if(ob->query("menpai/"+family+"/family")==family) {
                message_vision(CYN"$n对$N道："+ob->query("menpai/"+family+"/name")+
                        "("+ob->query("menpai/"+family+"/id")+")"+
                        "已经提出举办掌门大弟子比武选拔大会啦！\n"NOR, me, ob);
                return 1;
        }

        ob->set("menpai/"+family+"/id", id);
        ob->set("menpai/"+family+"/name", name);
        ob->set("menpai/"+family+"/family", family);
        ob->set("menpai/"+family+"/long", "等待巫师审核中！");
        message_vision(CYN"$n掏出本子记了下来，对$N道：好！但是得等待巫师的批准！\n"NOR, me, ob);
        save();
        return 1;
}

int do_biwu(string arg)
{
        object ob = this_object();
        int i=ob->query("biwudahui");

        if(!arg) {
                printf(HIW"\n〖"+HIG"比武方式"+HIW"〗"NOR+
                        "%s（geren）"+HIM+BIWUA+"\t%s"+
                        HIM+BIWUB+"\t%s"+
                        HIM+BIWUC+"\t%s"+
                        HIM+BIWUD+"\n"NOR,
                        status_color(ob->query("fangshi"), BIWUA),
                        status_color(ob->query("fangshi"), BIWUB),
                        status_color(ob->query("fangshi"), BIWUC),
                        status_color(ob->query("fangshi"), BIWUD) );
                return 1;
        }
        switch(arg) {
        case "geren":
                ob->set("fangshi", BIWUA);
                message("channel:chat",
                        HIW"【比武场】现在比武场开放使用，大家可以随意前来比试！\n"NOR,users());
                save();
                return 1;
        case "leitai":
                ob->set("fangshi", BIWUB);
                message("channel:chat",
                        HIW"【比武场】现在比武场开放摆擂，欢迎各位高手前来摆擂！\n"NOR,users());
                save();
                return 1;
        case "menpai":
                ob->set("fangshi", BIWUC);
                message("channel:chat",
                        HIW"【比武场】现在比武场开放各门派比武，请向公平子申请！\n"NOR,users());
                save();
                return 1;
        case "xunhuan":
                ob->set("fangshi", BIWUD);
                message("channel:chat",
                        HIW"【比武场】现在第"+CHINESE_D->chinese_number(i)+
                        "届比武大会报名开始！"+"有意参加者请向公平子报名！\n"NOR,users());
                save();
                return 1;
        case "stop":
                ob->delete("fangshi");
                message("channel:chat",
                        HIW"【比武场】现在比武场暂停使用一端时间！\n"NOR,users());
                save();
                return 1;
        default:
                return notify_fail("目前比武方式只有："+
                        BIWUA+"、"+BIWUB+"、"+BIWUC+"、"+BIWUD+"！\n");
        }
}

int do_agree(string arg)
{
        object me=this_player();
        object ob=this_object();
        string menpai, str, family, name, id;

        if(sscanf(arg, "%s %s", menpai, str)!=2)
                return notify_fail("你要批准哪个门派举办掌门大弟子选拔比武申请？\n");

        family=ob->query("menpai/"+menpai+"/family");

        if(!family)
                return notify_fail("这个门派还未提出申请！\n");

        name=ob->query("menpai/"+menpai+"/name");
        id=ob->query("menpai/"+menpai+"/id");
        str="同意 于 "+str+"";
        ob->set("menpai/"+menpai+"/agree", "同意");
        ob->set("menpai/"+menpai+"/long", str);
        ob->set("menpai_baoming/"+family+"/"+id+"/id", id);
        ob->set("menpai_baoming/"+family+"/"+id+"/name", name);
        message_vision(CYN"$N批准了"+family+"举办掌门大弟子选拔比武申请！\n"NOR, me);
        message("channel:chat",
                HIW"【比武场】巫师批准了"+family+"举办掌门大弟子选拔比武申请，"+
                "请从速前来报名参加！\n"NOR,users());
        save();
        return 1;
}

int do_diss(string arg)
{
        object me=this_player();
        object ob=this_object();
        string menpai, str, family, name, id;

        if(sscanf(arg, "%s %s", menpai, str)!=2)
                return notify_fail("你要否决哪个门派举办掌门大弟子选拔比武申请？\n");

        family=ob->query("menpai/"+menpai+"/family");

        if(!family) 
                return notify_fail("这个门派还未提出申请！\n");

        name=ob->query("menpai/"+menpai+"/name");
        id=ob->query("menpai/"+menpai+"/id");
        str="不同意 因为 "+str+"";
        ob->set("menpai/"+menpai+"/long", str);
        ob->delete("menpai/"+menpai+"/agree");
        ob->delete("menpai_baoming/"+family+"");
        message_vision(CYN"$N否决了"+family+"举办掌门大弟子选拔比武申请！\n"NOR, me);
        save();
        return 1;
}

int do_del(string arg)
{
        object me=this_player();
        object ob=this_object();
        string family;

        family=ob->query("menpai/"+arg+"/family");

        if(!family) 
                return notify_fail("这个门派还未提出申请！\n");

        ob->delete("menpai/"+family+"");
        ob->delete("menpai_baoming/"+family+"");
        message_vision(CYN"$N删除了"+family+"举办掌门大弟子选拔比武申请！\n"NOR, me);
        save();
        return 1;
}

string status_color(string current, string str)
{
        if(str==current) return BLINK HIG"●"NOR;
        return HIR"●"NOR;
}

string delcolor(string str2)
{
        str2 = replace_string(str2, BLK,"");
        str2 = replace_string(str2, RED,"");
        str2 = replace_string(str2, GRN,"");
        str2 = replace_string(str2, YEL,"");
        str2 = replace_string(str2, BLU,"");
        str2 = replace_string(str2, MAG,"");
        str2 = replace_string(str2, CYN,"");
        str2 = replace_string(str2, WHT,"");
        str2 = replace_string(str2, HIR,"");
        str2 = replace_string(str2, HIG,"");
        str2 = replace_string(str2, HIY,"");
        str2 = replace_string(str2, HIB,"");
        str2 = replace_string(str2, HIM,"");
        str2 = replace_string(str2, HIC,"");
        str2 = replace_string(str2, HIW,"");
        str2 = replace_string(str2, NOR,"");
        str2 = replace_string(str2, BLINK,"");
        return str2;
}

