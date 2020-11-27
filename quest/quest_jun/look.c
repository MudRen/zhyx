// look.c
// modified by xingyun �����ƶ���̬С��ͼ

#include <room.h>
#include <ansi.h>
inherit F_CLEAN_UP;
#define TIME_TICK1 ((time()-900000000)*24)
string draw_map(string *dirs,mapping exits,object me);
string *all_exits = ({
    "east",
    "south",
    "west",
    "north",
    "eastup",
    "southup",
    "westup",
    "northup",
    "eastdown",
    "southdown",
    "westdown",
    "northdown",
    "northeast",
    "northwest",
    "southeast",
    "southwest",
    "up",
    "down",
    "enter",
    "out",
});

string *look_level_boy = ({
 BLU "ü����б����ͷѢ�ţ���������" NOR,
 BLU "�������죬������ף�����ޱ�" NOR,
 BLU "�����Ƥ��ͷ���������˲����ٿ��ڶ���" NOR,
 HIB "��ü���ۣ�������ߣ�������״" NOR,
 HIB "��ͷ�������Բ��ģ��ֽŶ̴֣����˷�Ц" NOR,
 NOR "��հ��ݣ��ݹ����꣬������̾" NOR,
 NOR "ɵͷɵ�ԣ��ճպ�����������Ҳ��ʵ" NOR,
 NOR "��òƽƽ�������������ʲôӡ��" NOR,
 YEL "�����Բ���������⣬���ζ���" NOR,
 YEL "��Բ���������ڷ����Ǹ񲻷�" NOR,
 RED "üĿ���㣬�����󷽣�һ���˲�" NOR,
 RED "˫�۹⻪Ө��͸���������ǵĹ�â" NOR,
 HIY "�ٶ���������ˮ�����̷��飬������������Ŀ��" NOR,
 HIY "˫Ŀ���ǣ�ü�Ҵ��飬�������޲�Ϊ֮�Ķ�" NOR,
 HIR "�����촽�����˿��Σ���ֹ��������" NOR,
 HIR "��������Ŀ�����ǣ����˹�Ŀ����" NOR,
 MAG "�������񣬷�ױ��������������" NOR,
 MAG "Ʈ�ݳ�������������" NOR,
 MAG "�����ʣ��������������������ٷ�" NOR,
 HIM "������ˬ���Ǹ����棬��������" NOR,
 HIM "һ���������ȣ��ɷ���ǣ���ֹ����" NOR,
});

string *look_level_girl = ({
  BLU "�������Σ�״��ҹ��" NOR,
  BLU "���б�ۣ���ɫ�Ұܣ�ֱ����һ��" NOR,
  BLU "����ü�������ۣ���Ƥ�Ʒ�������һ��������" NOR,
  HIB "��С�綹��üëϡ�裬�����צ����������" NOR,
  HIB "һ�����������һ����û�ø�" NOR,
  NOR "�������Ƥɫ�ֺڣ���ª����" NOR,
  NOR "�ɻƿ��ݣ���ɫ���ƣ�����Ů��ζ" NOR,
  YEL "�����С�������޹⣬��������" NOR,
  YEL "�䲻���£���Ҳ�׾�����Щ����֮��" NOR,
  RED "����΢�ᣬ�ŵ��������¿���" NOR,
  RED "�������ģ�����Ө͸��������˼" NOR,
  HIR "��С���磬���������������������" NOR,
  HIR "�������󣬼���ʤѩ��Ŀ����ˮ" NOR,
  HIW "���۰���������ҩ���̣����￴��" NOR,
  HIW "����ϸ������欶��ˣ�����һ������������" NOR,
  MAG "�����������������£�����ܳ�������" NOR,
  MAG "üĿ�续������ʤѩ�����ν�����߻�" NOR,
  MAG "�������������Ż���ɽ�����˼�֮����" NOR,
  HIM "������ϼ���������񣬻�����������" NOR,
  HIM "�������ɣ���մһ˿�̳�" NOR,
  HIM "����"+HIW+"������"+HIM+"�������ƻã��Ѳ����Ƿ�������" NOR,
});
int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string cdir( string dir );
string cterrain( string terrain );
void create() { seteuid(getuid()); }
int main(object me, string arg)
{
        object obj;
        int result;

        if( !arg ) result = look_room(me, environment(me));
        else if( (obj = present(arg, me)) || (obj = present(arg, environment(me))))
        {
                if( obj->is_character() ) result = look_living(me, obj);
                else result = look_item(me, obj);
        } else result = look_room_item(me, arg);

        return result;
}

string clean_color(string arg)
{
        if(!arg)
                return "";
        arg = replace_string(arg, BLK, "");
        arg = replace_string(arg, RED, "");
        arg = replace_string(arg, GRN, "");
        arg = replace_string(arg, YEL, "");
        arg = replace_string(arg, BLU, "");
        arg = replace_string(arg, MAG, "");
        arg = replace_string(arg, CYN, "");
        arg = replace_string(arg, WHT, "");
        arg = replace_string(arg, HIR, "");
        arg = replace_string(arg, HIG, "");
        arg = replace_string(arg, HIY, "");
        arg = replace_string(arg, HIB, "");
        arg = replace_string(arg, HIM, "");
        arg = replace_string(arg, HIC, "");
        arg = replace_string(arg, HIW, "");
        arg = replace_string(arg, NOR, "");
        arg = replace_string(arg, BLINK,"");
        return arg;
}

int sort_exits(string str1,string str2)
{
    int i,j;
     if (strcmp(str1,"a")<0 && strcmp(str2,"a")<0){
         if (strlen(str1) < strlen(str2)) return -1;
         if (strlen(str1) == strlen(str2)) return strcmp(str1,str2);
         return 1;
     }else{
         i=member_array(str1, all_exits);
         j=member_array(str2, all_exits);
         if (i>0 && j>0) return i-j;
         else return strcmp(str1,str2);
     }
}

int look_room(object me, object env)
{
    int i,amount;
    object obj,room;
//        mixed *cmds;
    mapping exits,my;
    string str, *dirs,str2;
    if( !env ) {
        write("������ܻ����ɵ�һƬ��ʲ��Ҳû�С�\n");
        return 1;
    }


    if (!objectp(present("fire", me))
     && environment(me)->query("outdoors") 
     && NATURE_D->outdoor_room() && !wizardp(me) )
    {
     str = sprintf( HIC"%s"+NOR+HIC+"\n������̫���ˣ�ʲô�������塣\n"+NOR+"",
        env->query("short"));
     if( mapp(exits = env->query("exits")) ) {
        dirs = keys(exits);
        for(i=0; i<sizeof(dirs); i++)
            if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                dirs[i] = 0;
        dirs -= ({ 0 });
        if( sizeof(dirs)==0 )
            str += "��������û���κ����Եĳ�·��\n";
        else if( sizeof(dirs)==1 )
            str += "��������Ψһ�ĳ����� " + BOLD + dirs[0] + NOR + "��\n";
        else{
            dirs = sort_array(dirs,"sort_exits");
            str += sprintf("�����������Եĳ����� " + BOLD + "%s" + NOR + " �� " + BOLD + "%s" + NOR + "��\n",
                              implode(dirs[0..sizeof(dirs)-2], "��"), dirs[sizeof(dirs)-1]);
        }
      }else
            str += "��������û���κ����Եĳ�·��\n";
        write(str);
        return 1;
    }
        if(env->query("outdoors",1))
                str2 = NOR+HIC"����"NOR;
        if(!env->query("outdoors",1))
                str2 = NOR+HIC"����"NOR;
    if (wizardp(me) && !me->query("env/show_room"))
    str = sprintf( HIC"��"HIW"%s"HIC"����%s-"HIR"%s"
                 +NOR+" - "+RED+"%s\n"+NOR+"    %s",
        env->query("short"),str2,
        cterrain( (string)env->query("terrain") ),
        SECURITY_D->valid_read(file_name(env),me)? file_name(env): "",
        env->query("long"));
    else 
    str = sprintf(  HIC"��"HIW"%s"HIC"��  %s-"HIR"%s"+NOR+"\n    %s",
        env->query("short"),str2,cterrain( (string)env->query("terrain") ),
        env->query("long"));
    str+= env->query("outdoors")? NATURE_D->outdoor_room_description() : "";
    if( wizardp(me) && mapp(exits = env->query("exits")) ) {
        dirs = keys(exits);
        for(i=0; i<sizeof(dirs); i++)
        if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
             dirs[i] = 0;
        dirs -= ({ 0 });
        if( mapp(exits) ){
            str +="��������ĳ����У�\n";
            for (i=0;i<sizeof(dirs);i++){
                if (!room=find_object(exits[dirs[i]]))
                room=load_object(exits[dirs[i]]);
            if (room)   str+=sprintf(BOLD"����%-12s"+NOR+YEL+" --> "+CYN+"%-10s"+RED+"%s.c\n"+NOR,cdir( dirs[i] ),room->query("short"),exits[dirs[i]]);
            else    str+=sprintf(BOLD"����%-12s"+NOR+YEL+" --> "+RED+"û���������ڡ�\n"+NOR,cdir( dirs[i] ));
            }}}else

    if( !wizardp(me) && mapp(exits = env->query("exits")) ) {
        dirs = keys(exits);
        for(i=0; i<sizeof(dirs); i++)
        if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
              dirs[i] = 0;
        dirs -= ({ 0 });
      if( mapp(exits) ){
            str +="��������ĳ����У�";
            for (i=0;i<sizeof(dirs);i++)
            str += HIW+dirs[i]+"  "NOR;
            str += "\n"NOR;
            str+=draw_map(dirs,exits,env);
       }}else

            str += "��������û���κ����Եĳ�·��\n";

    i=0;
    foreach (obj in all_inventory(env)){
    if (!wizardp(me) && obj->query("no_show")) continue;
        if (!obj->is_character() && (i++)>99) continue;
        if (obj==me || !me->visible(obj) ){
            continue;
        }
        if (obj->query("money_id") 
            || !obj->query("unit")
            || obj->is_character()){
                if(!wizardp(me)){str+=sprintf("    %-12s\n",obj->short());}
                if(wizardp(me)){str+=sprintf("����%-28s" + YEL":"NOR + RED"%s" + ".c"NOR+ "\n",obj->short(),base_name(obj));}
            continue;
        }
        if (!mapp(my))
            my=([obj->query("unit")+obj->short():1]);
        else{
            amount=my[obj->query("unit")+obj->short()];
            my[obj->query("unit")+obj->short()]=amount+1;
        }
    }
    if (mapp(my)){
        dirs=keys(my);
        for (i=0;i<sizeof(my);i++)
                str+=sprintf("����%s%s\n",
my[dirs[i]]==1?"":CHINESE_D->chinese_number(my[dirs[i]]),
my[dirs[i]]==1?dirs[i][2..]:dirs[i]);
    }
    write(str);
    return 1;
}


string draw_map(string *dirs,mapping exits,object env)
{
      string str="";
      object room;
      string dir1="",dir2="",dir3="",dir4="",
                  dir5="",dir6="",dir7="",dir8="";
      string sign1="",sign2="",sign3="",sign4="",
                  sign5="",sign6="",sign7="",sign8=""; 

      if( member_array("northwest",dirs)!=-1 )
      {
       if (!room=find_object(exits["northwest"]))
                   room=load_object(exits["northwest"]);
       if (room)
                   dir1=clean_color(room->query("short"));
              else
                   dir1=RED"û���������ڡ�"NOR;

       sign1=HIW"\\"NOR;
      }
      if( member_array("up",dirs)!=-1 )
      {
       if (!room=find_object(exits["up"]))
                   room=load_object(exits["up"]);
       if (room)
                   dir2=clean_color(room->query("short"));
              else
                   dir2=RED"û���������ڡ�"NOR;

       sign2=HIW"|"NOR;
      }
      if( member_array("northup",dirs)!=-1 )
      {
       if (!room=find_object(exits["northup"]))
                   room=load_object(exits["northup"]);
       if (room)
                   dir2=clean_color(room->query("short"));
              else
                   dir2=RED"û���������ڡ�"NOR;

       sign2=HIW"|"NOR;
      }
      if( member_array("northdown",dirs)!=-1 )
      {
       if (!room=find_object(exits["northdown"]))
                   room=load_object(exits["northdown"]);
       if (room)
                   dir2=clean_color(room->query("short"));
              else
                   dir2=RED"û���������ڡ�"NOR;

       sign2=HIW"|"NOR;
      }                   
      if( member_array("north",dirs)!=-1 )
      {
       if (!room=find_object(exits["north"]))
                   room=load_object(exits["north"]);
       if (room)
                   dir2=clean_color(room->query("short"));                  
              else
                   dir2=RED"û���������ڡ�"NOR;

       sign2=HIW"|"NOR;
      }
      if( member_array("northeast",dirs)!=-1 )
      {
       if (!room=find_object(exits["northeast"]))
                   room=load_object(exits["northeast"]);
       if (room)
                   dir3=clean_color(room->query("short"));
              else
                   dir3=RED"û���������ڡ�"NOR;

       sign3=HIW"/"NOR;
      }
      if( member_array("out",dirs)!=-1 )
      {
       if (!room=find_object(exits["out"]))
                   room=load_object(exits["out"]);
       if (room)
                   dir4=clean_color(room->query("short"));
              else
                   dir4=RED"û���������ڡ�"NOR;

       sign4=HIW"��"NOR;       
      }
      if( member_array("westup",dirs)!=-1 )
      {
       if (!room=find_object(exits["westup"]))
                   room=load_object(exits["westup"]);
       if (room)
                   dir4=clean_color(room->query("short"));
              else
                   dir4=RED"û���������ڡ�"NOR;

       sign4=HIW"��"NOR;
      }
      if( member_array("westdown",dirs)!=-1 )
      {
       if (!room=find_object(exits["westdown"]))
                   room=load_object(exits["westdown"]);
       if (room)
                   dir4=clean_color(room->query("short"));
              else
                   dir4=RED"û���������ڡ�"NOR;

       sign4=HIW"��"NOR;
      }
      if( member_array("west",dirs)!=-1 )
      {
       if (!room=find_object(exits["west"]))
                   room=load_object(exits["west"]);
       if (room)
                   dir4=clean_color(room->query("short"));
              else
                   dir4=RED"û���������ڡ�"NOR;

       sign4=HIW"��"NOR;
      }
      if( member_array("enter",dirs)!=-1 )
      {
       if (!room=find_object(exits["enter"]))
                   room=load_object(exits["enter"]);
       if (room)
                   dir5=clean_color(room->query("short"));
              else
                   dir5=RED"û���������ڡ�"NOR;

       sign5=HIW"��"NOR;
      }
      if( member_array("eastup",dirs)!=-1 )
      {
       if (!room=find_object(exits["eastup"]))
                   room=load_object(exits["eastup"]);
       if (room)
                   dir5=clean_color(room->query("short"));
              else
                   dir5=RED"û���������ڡ�"NOR;

       sign5=HIW"��"NOR;
      }
      if( member_array("eastdown",dirs)!=-1 )
      {
       if (!room=find_object(exits["eastdown"]))
                   room=load_object(exits["eastdown"]);
       if (room)
                   dir5=clean_color(room->query("short"));
              else
                   dir5=RED"û���������ڡ�"NOR;

       sign5=HIW"��"NOR;
      }                   
      if( member_array("east",dirs)!=-1 )
      {
       if (!room=find_object(exits["east"]))
                   room=load_object(exits["east"]);
       if (room)
                   dir5=clean_color(room->query("short"));
              else
                   dir5=RED"û���������ڡ�"NOR;

       sign5=HIW"��"NOR;
      }
      if( member_array("southwest",dirs)!=-1 )
      {
       if (!room=find_object(exits["southwest"]))
                   room=load_object(exits["southwest"]);
       if (room)
                   dir6=clean_color(room->query("short"));
              else
                   dir6=RED"û���������ڡ�"NOR;

       sign6=HIW"/"NOR;
      }
      if( member_array("down",dirs)!=-1 )
      {
       if (!room=find_object(exits["down"]))
                   room=load_object(exits["down"]);
       if (room)
                   dir7=clean_color(room->query("short"));
              else
                   dir7=RED"û���������ڡ�"NOR;

       sign7=HIW"|"NOR;
      } 
      if( member_array("southup",dirs)!=-1 )
      {
       if (!room=find_object(exits["southup"]))
                   room=load_object(exits["southup"]);
       if (room)
                   dir7=clean_color(room->query("short"));
              else
                   dir7=RED"û���������ڡ�"NOR;

       sign7=HIW"|"NOR;
      }
      if( member_array("southdown",dirs)!=-1 )
      {
       if (!room=find_object(exits["southdown"]))
                   room=load_object(exits["southdown"]);
       if (room)
                   dir7=clean_color(room->query("short"));
              else
                   dir7=RED"û���������ڡ�"NOR;

       sign7=HIW"|"NOR;
      }
      if( member_array("south",dirs)!=-1 )
      {
       if (!room=find_object(exits["south"]))
                   room=load_object(exits["south"]);
       if (room)
                   dir7=clean_color(room->query("short"));
              else
                   dir7=RED"û���������ڡ�"NOR;

       sign7=HIW"|"NOR;
      }
      if( member_array("southeast",dirs)!=-1 )
      {
       if (!room=find_object(exits["southeast"]))
                   room=load_object(exits["southeast"]);
       if (room)
                   dir8=clean_color(room->query("short"));
              else
                   dir8=RED"û���������ڡ�"NOR;

       sign8=HIW"\\"NOR;
      }


     str = sprintf("        %s"HIG"%-12s"NOR, str, dir1);
     str = sprintf("%s   "HIG"%-12s"NOR, str, dir2);
     str = sprintf("%s   "HIG"%-12s\n"NOR, str, dir3);
     str = sprintf("%s                   %-2s", str, sign1);
     str = sprintf("%s     %-2s", str, sign2);
     str = sprintf("%s       %-2s\n", str, sign3);
     str = sprintf("%s        "HIG"%-12s"NOR, str, dir4);
     str = sprintf("%s%-2s", str, sign4);
     str = sprintf("%s "HIR"%-12s"NOR, str,env->query("short")); 
     str = sprintf("%s%-2s", str,sign5);
     str = sprintf("%s  "HIG"%-12s\n"NOR, str,dir5);
     str = sprintf("%s                   %-2s", str, sign6);
     str = sprintf("%s     %-2s", str, sign7);
     str = sprintf("%s       %-2s\n", str, sign8);
     str = sprintf("%s        "HIG"%-12s"NOR, str, dir6);
     str = sprintf("%s   "HIG"%-12s"NOR, str, dir7);
     str = sprintf("%s   "HIG"%-12s\n"NOR, str, dir8);

     return str;
}

int look_item(object me, object obj)
{
    mixed *inv;
    if (!me->visible(obj))
    { write("��Ҫ��ʲô��\n"); return 1; }

    me->start_more(obj->short() + HIW"��"NOR + obj->long());
    inv=all_inventory(obj);
    if( sizeof(inv) ) {
    inv = map_array(inv, "inventory_look", this_object() );  
    message("vision", sprintf("�����У�\n  %s\n",
            implode(inv, "\n  ") ), me);
    }
    return 1;
}
int look_room_item(object me, string arg)
{
        object env;
        mapping item, exits;

        if( !objectp(env = environment(me)) )
                return notify_fail("����ֻ�л����ɵ�һƬ��ʲôҲû�С�\n");
        if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
                if( stringp(item[arg]) )
                        write(item[arg]);
                else if( functionp(item[arg]) )
                        write((string)(*item[arg])(me));

                return 1;
        }
        if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
                if( objectp(env = find_object(exits[arg])) )
                        look_room(me, env);
                else {
                        call_other(exits[arg], "???");
                        look_room(me, find_object(exits[arg]));
                }
                return 1;
        }
        return notify_fail("��Ҫ��ʲô��\n");
}
int look_living(object me, object obj)
{
    int per_temp,i,j;
    string str, pro,*skills_name;
    mixed *inv;
    mapping my_fam, fam,skills;
    if( me!=obj )
        message("vision", me->name() + "�������㿴����֪����Щʲ�����⡣\n", obj);
    if (!objectp(present("fire", me))  && environment(me)->query("outdoors") && NATURE_D->outdoor_room() && !wizardp(me) ){
    str = sprintf( HIC"\n    �㿴��ǰ���ƺ��и���Ӱ������̫���ˣ������塣\n"NOR);
        write(str);
        return 1;
    }
    str = obj->long();
    pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));
    if( (string)obj->query("race")=="����"
    &&  intp(obj->query("age")) )
        str += sprintf("%s������Լ%s���ꡣ\n", pro, chinese_number(obj->query("age") / 10 * 10));
    per_temp= (obj->query_per()>=30)?20:(obj->query_per()-10);
    if (per_temp<0) per_temp=0;
    if ( (string)obj->query("race")=="����" ) {
    if ( (string)obj->query("gender") == "Ů��")
        str += sprintf("%s����%s��\n", pro, look_level_girl[per_temp]);
    else
        str += sprintf("%s����%s��\n", pro, look_level_boy[per_temp]);
    skills=obj->query_skills();
    if (!sizeof(skills))
        str+=sprintf("%s�������ƺ������κ��书��\n", pro);
    else{
        skills_name=sort_array( keys(skills), (: strcmp :) );
        i=random(sizeof(skills_name));
                if (SKILL_D(skills_name[i])->type()=="knowledge")
            str+=sprintf("%s�������ƺ������κ��书��\n", pro);
        else
              str+=sprintf("%s���书�������ƺ�%s��\n", pro,"/cmds/skill/skills"->skill_level(SKILL_D(skills_name[i])->type(), skills[skills_name[i]]));
    }
    }
    // If we both has family, check if we have any relations.
    if( obj!=me
    &&  mapp(fam = obj->query("family"))
    &&  mapp(my_fam = me->query("family")) 
    &&  fam["family_name"] == my_fam["family_name"] ) {
    
        if( fam["generation"]==my_fam["generation"] ) {
            if( (string)obj->query("gender") == "����" )
                str += sprintf( pro + "�����%s%s��\n",
                    my_fam["master_id"] == fam["master_id"] ? "": "ͬ��",
                    my_fam["enter_time"] > fam["enter_time"] ? "ʦ��": "ʦ��");
            else
                str += sprintf( pro + "�����%s%s��\n",
                    my_fam["master_id"] == fam["master_id"] ? "": "ͬ��",
                    my_fam["enter_time"] > fam["enter_time"] ? "ʦ��": "ʦ��");
        } else if( fam["generation"] < my_fam["generation"] ) {
            if( my_fam["master_id"] == obj->query("id") )
                str += pro + "�����ʦ����\n";
            else if( my_fam["generation"] - fam["generation"] > 1 )
                str += pro + "�����ͬ�ų�����\n";
            else if( fam["enter_time"] < my_fam["enter_time"] )
                str += pro + "�����ʦ����\n";
            else
                str += pro + "�����ʦ�塣\n";
        } else {
            if( fam["generation"] - my_fam["generation"] > 1 )
                str += pro + "�����ͬ������\n";
            else if( fam["master_id"] == me->query("id") )
                str += pro + "����ĵ��ӡ�\n";
            else
                str += pro + "�����ʦֶ��\n";
        }
    }
    if( obj->query("max_qi") )
        str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_qi") * 100 / (int)obj->query("max_qi")) + "\n";
    inv = all_inventory(obj);
    if( sizeof(inv) ) {
        inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
        inv -= ({ 0 });
        if( sizeof(inv) )
            str += sprintf( obj->is_corpse() ? "%s����������:\n%s\n" : "%s%s\n",
                            pro, implode(inv, "\n") );
        if (!obj->query_temp("armor/cloth") && obj->query("race")=="����" )
            str+=pro+"����"+YEL+"����"+NOR+"��ʲôҲû����\n";
    }   else    str += sprintf( obj->is_corpse() ? "%s��������ʲôҲû�С�\n" : (obj->query("race")=="����"?"%s����"+YEL+"����"+NOR+"��ʲôҲû����\n":"��������û���κζ�����\n"),pro);
    if (strlen(str)>8192)
    me->start_more(str);
    else     message("vision", str, me);
    if( obj!=me && living(obj)){
        i=obj->query("shen");
        j=me->query("shen");
        if ((i<-1000 && j>1000 ) || (i>1000 && j<-1000 ) ){
            write( obj->name() + "ͻȻת��ͷ������һ�ۡ�\n");
            COMBAT_D->auto_fight(obj, me, "berserk");
        }
    }
    return 1;
}

string inventory_look(object obj, int flag)
{
    string str;
     if( !flag )
          return "      "+obj->short();
    if( obj->query("equipped") ){
            switch( obj->query("armor_type") ) {
                case "cloth":
                case "armor":   str = "��";break; break;
                case "boots":   str = "�Ŵ�";break; break;
                case "head":    str = "ͷ��";break;
                case "neck":    str = "��Χ";break;
                case "finger":  str = "��ָ�ϴ���";break;
                case "hands":   str = "��������";break;
                case "waist":   str = "�������";break;
}
}
}
string cdir( string dir )
{
        switch( dir ) {
                case "east":
                        return "����(e)";
                case "west":
                        return "����(w)";
                case "south":
                        return "�Ϸ�(s)";
                case "north":
                        return "����(n)";
                case "up":
                        return "�Ϸ�(u)";
                case "down":
                        return "�·�(d)";
                case "northeast":
                        return "������(ne)";
                case "southeast":
                        return "���Ϸ�(se)";        
                case "southwest":
                        return "���Ϸ�(sw)";        
                case "northwest":
                        return "������(nw)";
                case "eastup":
                        return "���Ϸ�(eu)";        
                case "eastdown":
                        return "���·�(ed)";        
                case "westup":
                        return "���Ϸ�(wu)";        
                case "westdown":
                        return "���·�(wd)";                
                case "southup":
                        return "���Ϸ�(su)";
                case "southdown":
                        return "���·�(sd)";        
                case "northup":
                        return "���Ϸ�(nu)";
                case "northdown":
                        return "���·�(nd)";        
                case "out":
                        return "����(out)";        
                case "enter":
                        return "����(ENTER)";                        
                default:
                        return dir;
        }
}
string cterrain( string terrain )
{
        switch( terrain ) {
                case "plain":
                        return "ƽ��";
                case "hill":
                        return "����";
                   case "shop":
                         return "�̵�";
                case "mountain":
                        return "ɽ��";
                case "river":
                        return "�Ӵ�";
                case "ocean":
                        return "����";
                case "atmosphere":
                        return "����Ȧ";
                case "space":
                        return "����ռ�";
                default:
                        return "ƽ��";
        }
}
int help (object me)
{
        write(@HELP
ָ���ʽ: look [<��Ʒ>|<����>|<����>]
 
���ָ������鿴�����ڵĻ�����ĳ����Ʒ��������Ƿ���
 
�ο�: vl, sl
HELP
);
        return 1;
}
