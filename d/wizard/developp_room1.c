inherit ROOM;
void create()
{
        set("short", "����㳡");
        set("long", @LONG
________________________________________________________________________________
LONG
        );
          set("no_fight", 1); 
               set("no_clean_up", 0); 
         set("sleep_room", 1);
        set("valid_startroom", 1);
               setup();
}

void init()
{
object room;
if(wizardp(this_player()))
{
if(!room = find_object("/d/wizard/hall"))
room = load_object("/d/wizard/hall");
this_player()->move(room);
   }
 }
