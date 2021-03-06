//Edit By gladiator

#define TEACH_DIR       "/u/gladiator/employ_teacher"
#define TEACH_FILENAME  "teach.s"

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SAVE;

mapping *notes;

string query_save_file()
{
        return TEACH_DIR + TEACH_FILENAME ;
}

void done_post(object me, mapping note, string text)
{
    int i;
    note["msg"] = text;
    
    i = sizeof(notes);
    for( ; i > 0; i-- ) 
        if( notes[i-1]["author"] == me->query("id") ) break;
    
    if( !pointerp(notes) || i > 0 )
        if(!sizeof(notes)) notes = ({ note });
        else {
            notes[i-1]["title"] = note["title"];
            notes[i-1]["author"] = note["author"];
            notes[i-1]["msg"] = note["msg"];
            notes[i-1]["time"] = note["time"];
            notes[i-1]["solve"] = "";
             }
        else
            notes += ({ note });
            tell_object(me, HIY "新手求教信息输入完毕。你的信息已经被加到新手导师通知队列里。\n");
            tell_object(me, HIY "新手导师正在处理其他玩家，请等待。\n");
            tell_object(me, HIY "你可以先忙你自己的事情，过一段时间后可以用teach read查看"
                                "是否解决，或回复。\n" NOR);
        save();
    return;
}

void list_bug(object me)
{
    int i;
    string str,s;
    if (sizeof(notes)<1) {
        write("没有新手发出求教信息。\n");
        return;
    } 
    s = sprintf("新手发出的求教列表如下:\n"
                "----------------------------------------------------------------------\n");
    for( i = 0; i<sizeof(notes); i++){
        str = sprintf("%d) %-50s %10s %s \n",
                           i+1, notes[i]["title"], notes[i]["solve"]==""?"No solved":"By "+notes[i]["solve"],
                           ctime(notes[i]["time"])[0..9] );
        s = s + str;
    }
    me->start_more(s);                
}

void do_read(object me, int i) 
{
    string s;
    if( i > sizeof(notes) || i < 1) {
        write("无此编号!!\n");
        return;
    }
    s = sprintf("%d) %-50s %10s %s\n"
              "----------------------------------------------------------------------\n"
              "%s",
               i, notes[i-1]["title"], notes[i-1]["solve"]==""?"No solved":"By "+notes[i-1]["solve"],
               ctime(notes[i-1]["time"])[0..9], notes[i-1]["msg"] );
    me->start_more(s);
}

int search_id(string id)
{
    int i;
    if( !(i = sizeof(notes)) ) return 0;
    for( ; i > 0; i-- ) 
        if( notes[i-1]["author"] == id ) break;
    return i;
}

int do_solve(object me, int i)
{
    if( i > sizeof(notes) || i < 1) {
        write("无此编号!!\n");
        return 0;
    } 
    if ( notes[i-1]["solve"]!="" ) {
        write(notes[i-1]["solve"]+"已经标志啦!\n");
        return 1;
    }
    notes[i-1]["solve"] = me->query("id");
    save();
    write("该求教信息已标志为解决。\n");
    return 1;
}

int main(object me, string arg)
{
    mapping note;
    object where;
    string s, str,arg1; 
    int i, arg2;
    restore();
    
    if (!arg) {
        if(!wiz_level(me))
        {
            tell_object(me, HIY "你正在" HIY MUD_NAME HIY "里辛苦地挖着泥巴，突然发现不知道该怎么弄了。\n" NOR);
            tell_object(me, HIY "你赶紧向新手导师发出紧急求教信号：HELP！！！\n" NOR);
            where = environment(me);
            if (!where) 
                s=sprintf("%s(%s)求教",
                        (string)me-> name(),
                        (string)me-> query("id"));
            else
                s=sprintf("%s(%s)在%s(%s)求教",
                        (string)me->name(),
                        (string)me->query("id"),
                        (string)where ->query("short"),
                        (string)file_name(where));
            note = allocate_mapping(5);
            note["title"] = s;
            note["author"] = me->query("id"); 
            note["time"] = time();
            note["solve"] = "";
            me->edit( (: done_post, me, note :) );
        }
        else {
            list_bug(me);
        }
        return 1;
    } 

    if( sscanf(arg, "%s %s", s, arg1) == 2 ) {
        if( !wiz_level(me) || !me->query("employ/job")) return notify_fail("你无此权限，具体使用方法请参阅 help teach \n");
        if ( s != "solve" ) return notify_fail("格式不对，具体使用方法请参阅 help teach \n");
        if ( arg1 == "all" ) {
           if( !(i = sizeof(notes)) ) return notify_fail("没人发出求教信息。\n");
           for( ; i > 0; i-- ) 
               notes[i-1]["solve"] = me->query("id");
           write("所有的求教信息已经解决了。\n");
           return 1;
        }
        i = search_id(arg1);
        if( i > 0 ) { 
            do_solve( me, i );
            return 1;
        }
    }
    if( sscanf(arg, "%s %d", s, arg2) == 2 ) {
        if( !wiz_level(me) || !me->query("employ/job")) return notify_fail("你无此权限，具体使用方法请参阅 help teach \n");
        if ( s != "solve" || !me->query("employ/jon")) return notify_fail("你无此权限，具体使用方法请参阅 help teach \n");
        do_solve( me, arg2 ); 
        return 1;
    }
    if ( sscanf(arg, "%s", s) == 1 ) 
    switch(arg){
        case "read":       
            if( !(i = sizeof(notes)) )
                return notify_fail("还没有人发出求教信息！\n");
            else {
                i = search_id( me->query("id") );
                do_read(me,i);
            }
            break;
        case "list":
            if( !wiz_level(me) || !me->query("employ/job") ) return notify_fail("格式不对，具体使用方法请参阅 help teach \n");
            list_bug(me);
            break;
        case "pack":
            if( !wiz_level(me) ) return notify_fail("你无权删除求教信息，具体使用方法请参阅 help teach \n");
            if( !(i = sizeof(notes)) ) return notify_fail("没有人发出求教信息。\n");
            for( ; i > 0; i-- ) 
                if( "" != notes[i-1]["solve"] ) {
                    printf("%s的求教信息已经被删除了！\n", notes[i-1]["author"]);
                    if( sizeof(notes) == 1 ) notes = ({});
                    else if(i==1) notes = notes[1..sizeof(notes)-1];
                    else if( i == sizeof(notes) ) notes = notes[0..sizeof(notes)-2];
                    else notes = notes = notes[0..i-2] + notes[i..sizeof(notes)-1];
                }
            save();
            break;
        case "solve":
            if( !wiz_level(me) || !me->query("employ/job") ) return notify_fail("你无此权限，具体使用方法请参阅 help teach \n");
            return notify_fail("格式: teach solve <编号或玩家id>\n");
            break;
        default:
            if( !wiz_level(me) ) return notify_fail("格式不对，具体使用方法请参阅 help teach \n");
            if( sscanf(arg, "%d", i) == 1 )
                do_read( me, i );
            else if( sscanf( arg, "%s", str ) == 1 ) {
                i = search_id(str);
                if( i == 0 ) return notify_fail("无此玩家发出的求教信息！\n");
                do_read( me, i );
            }
    }
    else return notify_fail("格式不对，具体使用方法请参阅 help teach \n");
    return 1;
}

int help(object me)
{
        if (!wiz_level(me) )
        write(@HELP
指令格式 : 
           teach
           teach read
这个指令可以让新手向新手导师求助。
输入该命令后，系统将提示你输入求教内容的描述。玩家在这里应该将
出现的情况和想要请教的内容说清楚，以便让新手导师帮助解决。
每个玩家只能贴一条求教信息，新的求教信息将覆盖以前的输入。
可以用 teach read 阅读自己贴出的求教信息。
HELP
    );
        else 
write(@HELP
指令格式 : 
           teach
           teach <号码或玩家id>
           teach list
           teach pack
           teach solve <号码或玩家id>
这个指令可以辅助新手导师处理玩家提出的求教。teach 和 teach list 的功能一样，
都是将所有的求教信息进行列表。带参数的teach命令，根据参数的不同，将显示
对应号码或对应玩家求教的详细信息。teach solve用来标志某个求教信息已经被解决了。
teach pack 将删除所有已经标志为解决了的求教信息。
HELP
    );
    return 1;
}

