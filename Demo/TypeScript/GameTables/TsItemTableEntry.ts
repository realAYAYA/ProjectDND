import * as UE from "ue";
// =============================================================================
// *** BEGIN WRITING YOUR CODE - ***

// *** END WRITING YOUR CODE - ***
// =============================================================================

class TsItemTableEntry extends UE.Object {

    /** 道具Id */
    //@cpp:int    
    Id: number;

    /** 道具名称 */    
    Name: string;

    /** 分类 */
    //@cpp:int    
    Type: number;

    /** 品质 */
    //@cpp:int    
    Quality: number;

    /** 叠加上限 */
    //@cpp:int    
    MaxStack: number;

    /** 售价 */
    //@cpp:int    
    Price: number;

    /** 道具描述 */    
    Description: string;

    /** 道具图标 */    
    Icon: UE.TSoftObjectPtr<UE.Texture2D>;

    // =========================================================
    // *** BEGIN WRITING YOUR CODE _ ***

    // *** END WRITING YOUR CODE _  ***
    // =========================================================
    
    InitData(): boolean {
        // =========================================================
        // *** BEGIN WRITING YOUR CODE . ***

        // *** END WRITING YOUR CODE .  ***
        // =========================================================    
        return true
    }    
}

export default TsItemTableEntry