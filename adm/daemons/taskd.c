// Created by Axiao (08/21/2000)
// taskd.c

#include <ansi.h>
inherit F_DBASE;
mapping *quests;
mapping *read_table(string file);
string  *roomlines = ({
	"/d/llzhuang/lou0",
	"/d/llzhuang/lou1",
	"/d/llzhuang/lou2",
	"/d/llzhuang/lou3",
	"/d/llzhuang/lou4",
	"/d/llzhuang/lou5",
	"/d/llzhuang/lou6",
	"/d/llzhuang/lou7",
	"/d/llzhuang/lou8",
	"/d/llzhuang/lou9",
	"/d/llzhuang/stone1",
	"/d/llzhuang/stone2",
	"/d/llzhuang/stone3",
	"/d/llzhuang/stone4",
	"/d/llzhuang/stone5",
	"/d/llzhuang/stone6",
	"/d/llzhuang/stone7",
	"/d/llzhuang/stone8",
});

string  *rooms = ({
	"/d/llzhuang/lou0",
	"/d/llzhuang/lou1",
	"/d/llzhuang/lou2",
	"/d/llzhuang/lou3",
	"/d/llzhuang/lou4",
	"/d/llzhuang/lou5",
	"/d/llzhuang/lou6",
	"/d/llzhuang/lou7",
	"/d/llzhuang/lou8",
	"/d/llzhuang/lou9",
	"/d/llzhuang/stone1",
	"/d/llzhuang/stone2",
	"/d/llzhuang/stone3",
	"/d/llzhuang/stone4",
	"/d/llzhuang/stone5",
	"/d/llzhuang/stone6",
	"/d/llzhuang/stone7",
	"/d/llzhuang/stone8",
	"/d/llzhuang/shishi",
});

mapping *dynamic_quest1 = ({
([      "file_name":              "/quest/obj/afrji",
        "owner_name":             "/d/city/npc/aqingsao",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/bstu",
        "owner_name":             "/d/city/npc/zhu",
        "fin_func":               "big_reward",
]),
([      "file_name":              "/quest/obj/dzmwen",
        "owner_name":             "/d/city/npc/yang",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/hgyituo",
        "owner_name":             "/d/city/npc/smith",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/hongbao",
        "owner_name":             "/d/city/npc/xian",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/jiledan",
        "owner_name":             "/d/city/npc/guanjia",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/jygu",
        "owner_name":             "/d/city/npc/cheng",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/kaoti",
        "owner_name":             "/d/city/npc/linpingzhi",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/msqi",
        "owner_name":             "/quest/quest1/linzhennan",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/wenyu",
        "owner_name":             "/kungfu/class/wudang/xi",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/magrobe",
        "owner_name":             "/kungfu/class/wudang/guxu",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/huaqun",
        "owner_name":             "/kungfu/class/wudang/yin",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/lubanchi",
        "owner_name":             "/kungfu/class/huashan/linghu",
        "fin_func":               "NULL",
]),
});

mapping *dynamic_quest2= ({
([      "file_name":              "/quest/obj/ngjiapu",
        "owner_name":             "/d/city/npc/tang",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/qipan",
        "owner_name":             "/d/changan/npc/zhifu",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/sqgonggui",
        "owner_name":             "/d/beijing/npc/kangqinwang",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/szjing",
        "owner_name":             "/d/beijing/npc/gu",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/wudanglu",
        "owner_name":             "/d/beijing/npc/dubi",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/wujianxinfa",
        "owner_name":             "/d/city/npc/shisong",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/wuxingbai",
        "owner_name":             "/d/baituo/npc/li",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/xmdaofa",
        "owner_name":             "/kungfu/class/ouyang/ouyangfeng",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/msqi",
        "owner_name":             "/kungfu/class/xiaoyao/goudu",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/xxge",
        "owner_name":             "/kungfu/class/ouyang/ouyangke",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/pearl",
        "owner_name":             "/kungfu/class/huashan/yue-wife",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/tianyi_poison",
        "owner_name":             "/kungfu/class/huashan/linghu",
        "fin_func":               "NULL",
]),
});

mapping *dynamic_quest3= ({
([      "file_name":              "/quest/obj/yingoupai",
        "owner_name":             "/kungfu/class/gaibang/kongkong",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/zhihuang",
        "owner_name":             "/kungfu/class/gaibang/zuo-qu",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/wandao",
        "owner_name":             "/kungfu/class/xingxiu/azi",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/lihuading",
        "owner_name":             "/kungfu/class/xingxiu/chuchen",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/shouyu",
        "owner_name":             "/kungfu/class/xingxiu/ding",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/lindao",
        "owner_name":             "/kungfu/class/xingxiu/shihou",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/daoqiao",
        "owner_name":             "/kungfu/class/xingxiu/zhaixing",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/shensibu",
        "owner_name":             "/kungfu/class/wudang/song",
        "fin_func":               "NULL",
]),
([      "file_name":              "/quest/obj/guyuehan",
        "owner_name":             "/kungfu/class/wudang/yu",
        "fin_func":               "NULL",
]),
});

string  *dynamic_quest = ({
	"dynamic_quest1",
        "dynamic_quest2",
        "dynamic_quest3",
});

int filter_listener(object ob)
{
        if (ob->query("env/no_task")) return 0;
        return 1;
}

varargs void clear_room();
varargs void init_dynamic_quest(int hard);
varargs int spread_quest(mapping one_quest, int hard);
object find_env(object ob);
varargs int already_spreaded(string str, int hard);
int quest_reward( object me, object who,object quest_item);
string time_period(int timep,object me);
string dyn_quest_list();
#define MAX_DIS 7
#define MAX_ALT  2
#define MAX_DIR  8
int max_time = 0;
void create()
{
        int choice;

        choice=random(3);
        if( choice == 0 ) 
                   quests = dynamic_quest1;
        else if( choice == 1 )
                   quests = dynamic_quest2;
        else quests = dynamic_quest3;

        clear_room();
        message("channel:chat", HIG"�������顿����ɽׯʹ�����¿�ʼ���䡣\n"NOR, users());
        max_time = time()+1800;
        remove_call_out("creat"); 
        call_out("create",1800);
}
string check_time(object me)
{
        int time;string ctime;
        time = max_time - time();
        if( time > 0 ) 
        {
        	ctime = time_period(time,me);
        	return ctime; 
        }
        else return "ʹ��ϵͳ���ںܿ����·��䡣\n";
}
string time_period(int timep, object me)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "��";
        else  time = "";

        if(h) time += chinese_number(h) + "Сʱ";
        if(m) time += chinese_number(m) + "��";
        time += chinese_number(s) + "��";
        return time;
}
int quest_reward(object me, object who,object quest_item)
{
        mapping quest;
        int exp, pot, score;
        object *listeners;
        
        quest = quest_item->query("dynamic_quest");
        if (base_name(who) != quest["owner_name"]) return 0;
        
        exp = 8000 + random(2000);
        pot = exp / 2;
        score = random(exp) / 10;
        
        me->add("combat_exp", exp);
        me->add("potential", pot);
        me->add("score", score);
        tell_object(me, "�㱻�����ˣ�\n" +
        	chinese_number(exp) + "��ʵս����\n"+
        	chinese_number(pot) + "��Ǳ��\n" +
        	chinese_number(score) + "���ۺ�����\n");

        listeners = filter_array(users(), (: filter_listener :));
        message("shout", HIG "��"HIG"����ɽׯ"HIG"��"NOR + HIG + "��˵" + me->query("name") + "�ɹ��İ�" +
                who->query("name") + "��"+quest_item->name()+HIG+"���˻�����\n            " + 
                me->query("name") + "�������ˣ�\n            " + HIY +
                chinese_number(exp) + HIG"��ʵս����\n            " + HIY +
                chinese_number(pot) + HIG"��Ǳ��\n            " + HIY + 
                chinese_number(score)+ HIG "���ۺ����ۡ�\n" NOR, listeners);

        me->add("TASK", 1);
        
        if (! undefinedp(quest["fin_func"]))
        	call_other(this_object(),quest["fin_func"],me,who,quest_item);
        	
        if(quest_item)
        	destruct(quest_item);
        	
        return 1;
}
void clear_room()
{
        object *inv,*unv,room;
        string localroom;
        int    i, j, k;

        for (i=0; i<sizeof(rooms); i++) 
        {
        	localroom = rooms[i];
       		room = load_object(localroom);
       		room->reset();
       		inv = all_inventory(room);
       		for (k=0; k<sizeof(inv); k++) 
       		{
         		if(userp(inv[k]))
        		{
        			unv= all_inventory(inv[k]);
        			for (j=0; j<sizeof(unv); j++) 
        			{
        				if(unv[j]->query("dynamic_quest"))
        					destruct(unv[j]);
         			}
        		}
     		}
    	}
    	
     	init_dynamic_quest(1);
}

varargs void init_dynamic_quest(int hard)
{
        int i;
        for (i=0; i < sizeof(quests); i++)
                spread_quest(quests[i], hard);
}

varargs int spread_quest(mapping quest, int hard)
{
        object obj0,obj1,obj2,obj3;
        object cur_obj;
        object next_obj;
        object tar;
        object *inv,*unv;
        object *target=({});
        int    i, j;
        string location;
        
        if (already_spreaded(quest["file_name"], hard)) return 0;
        
        reset_eval_cost();
        location = roomlines[random(sizeof(roomlines))];
        obj0 = find_object(location);
        
        if (obj0) obj0->reset();
        else obj0= load_object(location);
        
        cur_obj = obj0;
        cur_obj->set("no_clean_up",1);
        
        if (cur_obj)
        {
        	inv = all_inventory(cur_obj);
        	for (i=0; i<sizeof(inv); i++) 
        	{
        		if (inv[i]->is_character() && ! userp(inv[i]))
        			target += ({ inv[i] });
        		if (inv[i]->is_container()) target += ({ inv[i] });
                }
        }
        
        if (sizeof(target)) cur_obj = target[random(sizeof(target))];
        
        cur_obj->set("coor",1);
        
        if (cur_obj)
        {
        	tar = new(quest["file_name"]);
       		if (! tar ) 
       		{
        		write(quest["file_name"] + "not found��\n");
             		return 1;
       		}

        	tar->set("value", 0);
        	tar->set("no_steal", 1);
        	tar->set("no_put", 1);
                tar->set("no_uget", 1);
                tar->set("no_sell", 1);
        	tar->set("dynamic_quest", quest);
        	tar->move(cur_obj);
        	tar->set("questobj", 1);
        }
        return 1;
}

string dyn_quest_list()
{
        string output = "";
        object owner,item;
        int    i, max_task = sizeof(quests);
        
        for (i=0; i < sizeof(quests); i++)
        {
        	reset_eval_cost();
        	if (! objectp(owner = find_object(quests[i]["owner_name"])))
        		owner = load_object(quests[i]["owner_name"]);
        	if (! objectp(item = find_object(quests[i]["file_name"])))
        		item = load_object(quests[i]["file_name"]);
if( !item && find_player("yuchang") ) tell_object(find_player("yuchang"), "item : "  + quests[i]["file_name"]);
if( !owner && find_player("yuchang") ) tell_object(find_player("yuchang"), "owner : "  + quests[i]["owner_name"]);

        	if (already_spreaded(quests[i]["file_name"]))
        	{
        		if (random(2))
        			output += sprintf("%s��%s��%s��\n",owner->query("name"),item->query("name"),item->query("id"));
        		else
        			output = sprintf("%s��%s��%s��\n",owner->query("name"),item->query("name"),item->query("id")) + output;
        	}
        	else
        	{
        		if (max_task > 0)
        			max_task--;
        		if (random(2))
        			output += sprintf("%s��%s��%s��������ɡ�\n",owner->query("name"),item->query("name"),item->query("id"));
        		else
        			output = sprintf("%s��%s��%s��������ɡ�\n",owner->query("name"),item->query("name"),item->query("id")) + output;
        	}
        }
        return output+"\n������������������������������������������������������\nĿǰ����"+chinese_number(max_task)+"��ʹ���ȴ������ɡ�\n";
}

varargs int already_spreaded(string str,int hard)
{
        object ob, *ob_list;
        int    i;
        
        if (! str) return 0;
        if (hard)
        {
        	ob_list = children(str);
        	for (i=0; i<sizeof(ob_list); i++) 
        	{
                	ob = find_env(ob_list[i]);
                	if (ob)
                	{ 
                		ob_list[i]->move(VOID_OB);
                 		destruct(ob_list[i]);
             	 	}
        	}
        	return 0;
        }
        else
        {
        	if (! str) return 0;
        	ob_list = children(str);
        	for (i=0; i<sizeof(ob_list); i++) 
        	{
                	ob = find_env(ob_list[i]);
                	if (ob) return 1;
        	}
        	return 0;
        }
}

object find_env(object ob)
{
        while (ob)
        {
        	if(ob->query("coor") ) return ob;
        	else ob = environment(ob);
        }
        return ob;
}

mapping *read_table(string file)
{
        string  *line, *field, *format;
        mapping *data;
        int     i, rn, fn;

        line = explode(read_file(file), "\n");
        data = ({});
        for (i=0; i<sizeof(line); i++) 
        {
                if (line[i]=="" || line[i][0]=='#') continue;
                if (! pointerp(field)) 
                {
                        field = explode( line[i], ":" );
                        continue;
                }
                if (! pointerp(format) ) 
                {
                        format = explode( line[i], ":" );
                        continue;
                }
                break;
        }

        for (rn = 0, fn = 0; i<sizeof(line); i++) 
        {
                if (line[i]=="" || line[i][0]=='#') continue;
                if (! fn ) data += ({ allocate_mapping(sizeof(field)) });
                sscanf( line[i], format[fn], data[rn][field[fn]] );
                fn = (++fn) % sizeof(field);
                if (! fn ) ++rn;
        }
        return data;
}

void big_reward(object me, object who, object item)
{
        tell_object(me, "�����У���\n");
}

void execute_accept_object(object me, object who, object item)
{
        who->accept_object(me, item);
}

