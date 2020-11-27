 //add by fudan fy wizard_group
//for we want add a new method for player
//#pragma optimize
#include <ansi.h>
mapping *quests,quests_fin=([]);
mapping *read_table(string file);
void init_dynamic_quest(int hard);
varargs int spread_quest(mapping one_quest, int hard);
object find_env(object ob);
varargs int already_spreaded(mixed one_quest, int hard);
void auto_reset_quest(int count);
varargs int quest_reward( object me, object quest_item);
string *roomlines;
string dyn_quest_list();
#define MAX_DIS 7
#define MAX_ALT  2
#define MAX_DIR  8
string locate_obj(object me,string str);
void create()
{
        string file;
        int i;
        object item;
        string id;
        quests = read_table("/quest/dynamic_npc_quest");
      for( i=0; i < sizeof(quests); i++)
        {
        if(!objectp(item= find_object(quests[i]["file_name"])))
        item = load_object(quests[i]["file_name"]);
                id=item->query("name");
                quests_fin[id]="no";
        }

      file = read_file("/quest/dynamic_location");
      roomlines = explode(file,"\n"); 
        //CRON_D->set_last_hard_dis_npc();
        auto_reset_quest(100);
        //init_dynamic_quest(1);
}
int quest_reward(object me, object quest_item)
{
        mapping quest;
        string id;
   int hard;
        int exp,pot,score;
        if( wizhood(me)=="(dummy)") return 0;
        if( quest_item->query("killer") != me ) return 0;
        if( !quest = quest_item->query("dynamic_npc_quest")) return 0;
//      if(base_name(who) != quest["owner_name"]) return 0;
        
        id=quest["file_name"];
        if(     quests_fin[id]) return 0;
        quests_fin[id]=1;       
        if(me->query("combat_exp")>800000){
        exp=1000+random(100)*random(100)/4;
        pot=exp/8+random(exp/8)+random(exp/12)+random(exp/12);
        score=random(50)+1;
        }
        else {
          exp =(600+random(400)*random(100)/40);
          pot = exp/12+random(exp/12);
          score = random(15)+1*quest["hard"];}
         me->add("combat_exp",exp);
        me->add("potential",pot);
        me->add("score",score);
        tell_object(me,HIW"��ϲ�㣬�������һ������\n�㱻�����ˣ�\n" +
        chinese_number(exp) + "��ʵս����\n"+
        chinese_number(pot) + "��Ǳ��\n" +
        chinese_number(score)+"���ۺ�����\n������Ƶ��ռ�������ǰ����һ����\n"NOR);
        me->add("TASKNPC",1);
//      if( !undefinedp(quest["fin_func"]))
//      call_other(this_object(),quest["fin_func"], me, quest_item);
        return 1;
} 
varargs void init_dynamic_quest(int hard)
{
        int i;
        message("system", ""HIY"�������"HIW"�����س�����:"HIR "\n ����Ӣ�۱���������\n",users());
        for( i=0; i < sizeof(quests); i++)
        {
            spread_quest(quests[i],hard);
        }
        message("system", HIG "����������¹��˭�֡�\n" NOR,users());  
}
void auto_reset_quest(int count) {
        int delay;
   
        if(count >= 8) {
                message("system", HIY "\n\n����NPCʹ������һ���Ӻ����·ֲ���\n\n" NOR, users());
                EVENT_D->add_event(time()+60, this_object(), (: init_dynamic_quest, 1 :));
                count = 0;
                delay = time() + 900 + random(1800);            
        } else if(count >= 6) {
                message("system", HIY "\n\n����NPCʹ������" + chinese_number(9-count) + "���Ӻ����·ֲ���\n\n" NOR, users());
                delay = time() + 60;
        } else {
                init_dynamic_quest(0);                  
                delay = time() + 900 + random(1800);
        }
        count++;
        EVENT_D->add_event(delay, this_object(), (: auto_reset_quest, count :)); 
}
varargs int spread_quest(mapping quest, int hard)
{
        object obj0,obj1,obj2,obj3;
        object cur_obj;
        object next_obj;
        object tar;
        object *ob_list;
        object *inv;
        object *target=({});
        int i;
        string location;
        string id;
              // if(already_spreaded(quest["file_name"],hard)) return 0; 
               
        reset_eval_cost();
        location = TASK_D->random_room();
        
        obj0=find_object(location);
        if(obj0)
                obj0->reset();
        else
                obj0=load_object(location);
        cur_obj =obj0;
        if(cur_obj)
        {
        	
        	      quest["completed"]=0;
                ob_list = children(quest["file_name"]);
                if( sizeof(ob_list) )
                        if( ob_list[0]->is_fighting() )
                                return 0;
                        else destruct(ob_list[0]);
                tar = new(quest["file_name"]);
                tar->set("ALWAYS_ACTIVE",1);
                tar->set("dynamic_npc_quest",quest);
                tar->set("wimpy",50);
                id = quest["file_name"];
                quests_fin[ id ]=0;
                tar->move(cur_obj);
        }
       
        return 1;
} 
string dyn_quest_list()
{
        string title, nickname,id;
        string output="";
        object owner,item;
    int i;
    for( i=0; i < sizeof(quests); i++)
        {
                reset_eval_cost();
//      if(!objectp(owner= find_object(quests[i]["owner_name"])))
//      owner = load_object(quests[i]["owner_name"]);
//        if(!objectp(item= find_object(quests[i]["file_name"])))
        item = new(quests[i]["file_name"]);
                title =item->query("title");
                nickname=item->query("nickname");
              if(!title) title=" ";
               if(!nickname) nickname=" ";
       if(already_spreaded(quests[i]["file_name"]))
        {
                if(random(2))
                output += sprintf("%s%s%s��%s��\n",title, nickname, item->query("name"),item->query("id"));
                else
                output = sprintf("%s%s%s��%s��\n",title, nickname, item->query("name"),item->query("id")) + output;
        }
        else
       {
        if(random(2))
        output += sprintf("%s%s%s��%s��������ɡ�\n", title,nickname,item->query("name"),item->query("id"));
        else
        output = sprintf("%s%s%s��%s��������ɡ�\n", title,nickname,item->query("name"),item->query("id")) + output;
        }
        destruct(item);
        
        }
        
        return (output);
}
string locate_obj(object me,string strr)
{
        string *distance = ({
"����", "�ܽ�", "�ȽϽ�", "��Զ",
"����", "�Ƚ�Զ", "��Զ", "��Զ"
        });
        string *altitude =({
"�ߴ�", "�ط�", "�ʹ�"
        });
        string *directions=({
"��Χ","����", "�Ϸ�", "����","����",
"������","������","���Ϸ�","���Ϸ�"
        });
        object ob, tmpobj,where, *ob_list;
        object item,room;
        string output,dis,alt,dir;
        int i;
        int x,y,z,x0,y0,z0;
        int realdis;
        int tmp;
        string str="";
        reset_eval_cost();
        for( i=0; i < sizeof(quests); i++)
        {
        if(!objectp(item= find_object(quests[i]["file_name"])))
                item = load_object(quests[i]["file_name"]);
        if(item->query("id") == strr || item->query("name") == strr) str = quests[i]["file_name"];
        }
        if(str != "" && already_spreaded( "str") ) {
                room = environment(me);
                ob_list = children(str);
                for(i=0; i<sizeof(ob_list); i++) {
                ob=find_env(ob_list[i]);
                if(ob)
                {
                        x0= (int)room->query("coor/x");
                        y0= (int)room->query("coor/y");
                        z0= (int)room->query("coor/z");
                        x=(int)ob->query("coor/x")-x0;
                        y=(int)ob->query("coor/y")-y0;
                        z=(int)ob->query("coor/z")-z0;
                        realdis=0;
                        if(x<0)realdis-=x; else realdis+=x;
                        if(y<0)realdis-=y; else realdis+=y;
                        if(z<0)realdis-=z; else realdis+=z;
                        tmp =(int)  realdis/50;
                        if(tmp>MAX_DIS) tmp = MAX_DIS;
                        dis=distance[tmp];
                        if(z>0) alt=altitude[0];
                        if(z<0) alt=altitude[2];
                        if(z==0) alt=altitude[1];
                        if(x==0&&y==0) dir=directions[0];
                        if(x==0&&y>0) dir=directions[1];
                        if(x==0&&y<0) dir=directions[2];
                        if(x>0&&y==0) dir=directions[3];
                        if(x<0&&y==0) dir=directions[4];
                        if(x>0&&y>0) dir=directions[5];
                        if(x<0&&y>0) dir=directions[6];
                        if(x>0&&y<0) dir=directions[7];
                        if(x<0&&y<0) dir=directions[8];
        output = "��"+ob_list[i]->query("name")+"���ƺ���"+dir+dis+"��"+alt+"��\n";
        return output;
                }
                }
        }
        else 
        if(wizardp(me) || me->query("class") == "official")
        {
        tmpobj = find_player(strr);
        if(!tmpobj) tmpobj = find_living(strr);
        if(!tmpobj) return "";
        ob = find_env(tmpobj);
        room = environment(me);
        if(ob)
        {
                        x0= (int)room->query("coor/x");
                        y0= (int)room->query("coor/y");
                        z0= (int)room->query("coor/z");
                        x=(int)ob->query("coor/x")-x0;
                        y=(int)ob->query("coor/y")-y0;
                        z=(int)ob->query("coor/z")-z0;
                        realdis=0;
                        if(x<0)realdis-=x; else realdis+=x;
                        if(y<0)realdis-=y; else realdis+=y;
                        if(z<0)realdis-=z; else realdis+=z;
                        tmp =(int)  realdis/50;
                        if(tmp>MAX_DIS) tmp = MAX_DIS;
                        dis=distance[tmp];
                        if(z>0) alt=altitude[0];
                        if(z<0) alt=altitude[2];
                        if(z==0) alt=altitude[1];
                        if(x==0&&y==0) dir=directions[0];
                        if(x==0&&y>0) dir=directions[1];
                        if(x==0&&y<0) dir=directions[2];
                        if(x>0&&y==0) dir=directions[3];
                        if(x<0&&y==0) dir=directions[4];
                        if(x>0&&y>0) dir=directions[5];
                        if(x<0&&y>0) dir=directions[6];
                        if(x>0&&y<0) dir=directions[7];
                        if(x<0&&y<0) dir=directions[8];
        output = "��"+tmpobj->query("name")+"���ƺ���"+dir+dis+"��"+alt+"��\n";
        return output;
        }
        }
                return ""; 
}
varargs int already_spreaded(mixed filename,int hard)
{
        object npc;
//        int i;
       if( !stringp(filename)) return 0;
//        if(!objectp(npc= find_object( filename)))
//                      npc=load_object( filename);
//              write (id);
                if( quests_fin[filename] ) return 0;
                return 1;
} 
object find_env(object ob)
{
        while(ob)
        {
        if(ob->query("coor") ) return ob;
        else ob=environment(ob);
        }
        return ob;
}
mapping *read_table(string file)
{
        string *line, *field, *format;
        mapping *data;
        int i, rn, fn; 
        line = explode(read_file(file), "\n");
        data = ({});
        for(i=0; i<sizeof(line); i++) {
                if( line[i]=="" || line[i][0]=='#' ) continue;
                if( !pointerp(field) ) {
                        field = explode( line[i], ":" );
                        continue;
                }
                if( !pointerp(format) ) {
                        format = explode( line[i], ":" );
                        continue;
                }
                break;
        } 
        for( rn = 0, fn = 0; i<sizeof(line); i++) {
                if( line[i]=="" || line[i][0]=='#' ) continue;
                if( !fn ) data += ({ allocate_mapping(sizeof(field)) });
                sscanf( line[i], format[fn], data[rn][field[fn]] );
                fn = (++fn) % sizeof(field);
                if( !fn ) ++rn;
        }
        return data;
}
void big_reward(object me, object who, object item)
{
        tell_object(me,"�����У���\n");
} 
void execute_accept_object(object me, object who, object item)
{
        who->accept_object(me,item);
}  
