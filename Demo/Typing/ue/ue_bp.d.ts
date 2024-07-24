/// <reference path="puerts.d.ts" />
/// <reference path="zprotocol.d.ts" />
declare module "ue" {
    import {$Ref, $Nullable} from "puerts"

    import * as cpp from "cpp"

    import * as UE from "ue"

// __TYPE_DECL_START: 4CAAE8C84FADB85ED03C32A6769D2081
    namespace Game.Blueprints.Widgets.WBP_Wait {
        class WBP_Wait_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            Button_50: UE.Button;
            TextBlock_Wait: UE.TextBlock;
            WaitText: string;
            SetWaitInfo(NewVar: string) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WBP_Wait_C;
            static Load(InName: string): WBP_Wait_C;
        
            __tid_WBP_Wait_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 91FE9F724CEB29DFE6DAC0A0EA9BE7F3
    namespace Game.Blueprints.Widgets.WBP_SessionTip {
        class WBP_SessionTip_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Button: UE.Button;
            TextBlock_RoomInfo: UE.TextBlock;
            Session: UE.BlueprintSessionResult;
            Widget_Wait: UE.Game.Blueprints.Widgets.WBP_Wait.WBP_Wait_C;
            BndEvt__WBP_RoomTip_Button_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature() : void;
            ExecuteUbergraph_WBP_SessionTip(EntryPoint: number) : void;
            OnFailure_DDAD48944BEDC694ACA52EAF2FCA99F3() : void;
            OnSuccess_DDAD48944BEDC694ACA52EAF2FCA99F3() : void;
            SetSessionInfo(InSession: UE.BlueprintSessionResult) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WBP_SessionTip_C;
            static Load(InName: string): WBP_SessionTip_C;
        
            __tid_WBP_SessionTip_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 535B780E46021AABF4C605AD003C65D4
    namespace Game.Blueprints.Widgets.WBP_FindSessions {
        class WBP_FindSessions_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Button_Search: UE.Button;
            VerticalBox_RoomList: UE.VerticalBox;
            WidgetSwitcher_101: UE.WidgetSwitcher;
            Results: TArray<UE.BlueprintSessionResult>;
            Activate() : void;
            BndEvt__WBP_Login_Button_Search_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature() : void;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            DeActivate() : void;
            /*
             *Called when a widget is no longer referenced causing the slate resource to destroyed.  Just like
             *Construct this event can be called multiple times.
             */
            Destruct() : void;
            ExecuteUbergraph_WBP_FindSessions(EntryPoint: number) : void;
            InpActEvt_BackSpace_K2Node_InputKeyEvent_0(Key: UE.Key) : void;
            OnFailure_01D90A2241754FEE74BE509BF862D0D2(Results: TArray<UE.BlueprintSessionResult>) : void;
            OnSuccess_01D90A2241754FEE74BE509BF862D0D2(Results: TArray<UE.BlueprintSessionResult>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WBP_FindSessions_C;
            static Load(InName: string): WBP_FindSessions_C;
        
            __tid_WBP_FindSessions_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 693CB69742894C8F8FB46F840C83C57E
    namespace Game.Blueprints.Widgets.WBP_Main {
        class WBP_Main_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Button_Multiplayer: UE.Button;
            Button_NewGame: UE.Button;
            BndEvt__WBP_Main_Button_Multiplayer_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature() : void;
            BndEvt__WBP_Main_Button_NewGame_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature() : void;
            ExecuteUbergraph_WBP_Main(EntryPoint: number) : void;
            OnFailure_0831072541737670CEF268A4E2DEC7F9() : void;
            OnSuccess_0831072541737670CEF268A4E2DEC7F9() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WBP_Main_C;
            static Load(InName: string): WBP_Main_C;
        
            __tid_WBP_Main_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B5D7CBB743365ED3CF19BCB94D919707
    namespace Game.Migrates.Blueprints.ABP_CharacterBase {
        class ABP_CharacterBase_C extends UE.AnimInstance {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystemInstance;
            AnimBlueprintExtension_Base: UE.AnimSubsystemInstance;
            AnimGraphNode_Root_6: UE.AnimNode_Root;
            AnimGraphNode_Root_5: UE.AnimNode_Root;
            AnimGraphNode_Root_4: UE.AnimNode_Root;
            AnimGraphNode_Root_3: UE.AnimNode_Root;
            AnimGraphNode_Root_2: UE.AnimNode_Root;
            AnimGraphNode_Root_1: UE.AnimNode_Root;
            AnimGraphNode_LinkedInputPose: UE.AnimNode_LinkedInputPose;
            AnimGraphNode_Root: UE.AnimNode_Root;
            AnimGraphNode_TransitionResult_7: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_6: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_5: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_4: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_3: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_2: UE.AnimNode_TransitionResult;
            AnimGraphNode_LinkedAnimLayer_5: UE.AnimNode_LinkedAnimLayer;
            AnimGraphNode_StateResult_5: UE.AnimNode_StateResult;
            AnimGraphNode_LinkedAnimLayer_4: UE.AnimNode_LinkedAnimLayer;
            AnimGraphNode_StateResult_4: UE.AnimNode_StateResult;
            AnimGraphNode_LinkedAnimLayer_3: UE.AnimNode_LinkedAnimLayer;
            AnimGraphNode_StateResult_3: UE.AnimNode_StateResult;
            AnimGraphNode_UseCachedPose: UE.AnimNode_UseCachedPose;
            AnimGraphNode_StateResult_2: UE.AnimNode_StateResult;
            AnimGraphNode_StateMachine_1: UE.AnimNode_StateMachine;
            AnimGraphNode_TransitionResult_1: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult: UE.AnimNode_TransitionResult;
            AnimGraphNode_LinkedAnimLayer_2: UE.AnimNode_LinkedAnimLayer;
            AnimGraphNode_StateResult_1: UE.AnimNode_StateResult;
            AnimGraphNode_LinkedAnimLayer_1: UE.AnimNode_LinkedAnimLayer;
            AnimGraphNode_StateResult: UE.AnimNode_StateResult;
            AnimGraphNode_StateMachine: UE.AnimNode_StateMachine;
            AnimGraphNode_Slot: UE.AnimNode_Slot;
            AnimGraphNode_LinkedAnimLayer: UE.AnimNode_LinkedAnimLayer;
            AnimGraphNode_SaveCachedPose: UE.AnimNode_SaveCachedPose;
            K2Node_PropertyAccess_2: boolean;
            K2Node_PropertyAccess_1: UE.Vector;
            K2Node_PropertyAccess: UE.Vector;
            Velocity: UE.Vector;
            GroundSpeed: number;
            bShoudMove: boolean;
            bIsFalling: boolean;
            Anim_Idle: UE.AnimSequence;
            BS_WalkRun: UE.BlendSpace1D;
            Anim_Jump: UE.AnimSequence;
            Anim_FallLoop: UE.AnimSequence;
            Anim_Land: UE.AnimSequence;
            AnimGraph(AnimGraph: $Ref<UE.PoseLink>) : void;
            /*
             *Executed when the Animation Blueprint is updated on a worker thread, just prior to graph update
             */
            BlueprintThreadSafeUpdateAnimation(DeltaTime: number) : void;
            EvaluateGraphExposedInputs_ExecuteUbergraph_ABP_CharacterBase_AnimGraphNode_TransitionResult_B7D7C722457746C70B1BCB8E6A4B5916() : void;
            ExecuteUbergraph_ABP_CharacterBase(EntryPoint: number) : void;
            FullBody_Idle(FullBody_Idle: $Ref<UE.PoseLink>) : void;
            FullBody_JumpLoop(FullBody_JumpLoop: $Ref<UE.PoseLink>) : void;
            FullBody_JumpStart(FullBody_JumpStart: $Ref<UE.PoseLink>) : void;
            FullBody_Land(FullBody_Land: $Ref<UE.PoseLink>) : void;
            FullBody_WalkRun(FullBody_WalkRun: $Ref<UE.PoseLink>) : void;
            GetCharacterMovementComponent() : UE.CharacterMovementComponent;
            GetCurrentAcceleration() : UE.Vector;
            GetIsFalling() : boolean;
            PhySimulation(InPose: UE.PoseLink, PhySimulation: $Ref<UE.PoseLink>) : void;
            Update_FallingState() : void;
            Update_MoveSpeed() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ABP_CharacterBase_C;
            static Load(InName: string): ABP_CharacterBase_C;
        
            __tid_ABP_CharacterBase_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 97D4E1464FDDCBAFA7D63F82FED99214
    namespace Game.Migrates.Blueprints.ABP_XiaoShenBase {
        class AnimBlueprintGeneratedMutableData extends UE.AnimBlueprintMutableData {
            constructor();
            constructor(__FloatProperty: number);
            __FloatProperty: number;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_AnimBlueprintGeneratedMutableData_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 97D4E1464FDDCBAFA7D63F82FED99214
    namespace Game.Migrates.Blueprints.ABP_XiaoShenBase {
        class ABP_XiaoShenBase_C extends UE.AnimInstance {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            __AnimBlueprintMutables: UE.Game.Migrates.Blueprints.ABP_XiaoShenBase.AnimBlueprintGeneratedMutableData;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystemInstance;
            AnimBlueprintExtension_Base: UE.AnimSubsystemInstance;
            AnimGraphNode_Root_6: UE.AnimNode_Root;
            AnimGraphNode_SequencePlayer_3: UE.AnimNode_SequencePlayer;
            AnimGraphNode_Root_5: UE.AnimNode_Root;
            AnimGraphNode_BlendSpacePlayer: UE.AnimNode_BlendSpacePlayer;
            AnimGraphNode_Root_4: UE.AnimNode_Root;
            AnimGraphNode_SequencePlayer_2: UE.AnimNode_SequencePlayer;
            AnimGraphNode_Root_3: UE.AnimNode_Root;
            AnimGraphNode_SequencePlayer_1: UE.AnimNode_SequencePlayer;
            AnimGraphNode_Root_2: UE.AnimNode_Root;
            AnimGraphNode_SequencePlayer: UE.AnimNode_SequencePlayer;
            AnimGraphNode_Root_1: UE.AnimNode_Root;
            AnimGraphNode_LinkedInputPose: UE.AnimNode_LinkedInputPose;
            AnimGraphNode_SPCRJointDynamics: UE.AnimNode_SPCRJointDynamics;
            AnimGraphNode_KawaiiPhysics_9: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics_8: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics_7: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics_6: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics_5: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics_4: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics_3: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics_2: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics_1: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_KawaiiPhysics: UE.AnimNode_KawaiiPhysics;
            AnimGraphNode_ComponentToLocalSpace: UE.AnimNode_ConvertComponentToLocalSpace;
            AnimGraphNode_LocalToComponentSpace: UE.AnimNode_ConvertLocalToComponentSpace;
            AnimGraphNode_Root: UE.AnimNode_Root;
            K2Node_PropertyAccess_1: number;
            K2Node_PropertyAccess: UE.AnimInstance;
            Anim_Idle: UE.AnimSequence;
            BS_WalkRun: UE.BlendSpace1D;
            Anim_JumpStart: UE.AnimSequence;
            Anim_FallLoop: UE.AnimSequence;
            Anim_Land: UE.AnimSequence;
            AnimGraph(AnimGraph: $Ref<UE.PoseLink>) : void;
            ExecuteUbergraph_ABP_XiaoShenBase(EntryPoint: number) : void;
            FullBody_Idle(FullBody_Idle: $Ref<UE.PoseLink>) : void;
            FullBody_JumpLoop(FullBody_JumpLoop: $Ref<UE.PoseLink>) : void;
            FullBody_JumpStart(FullBody_JumpStart: $Ref<UE.PoseLink>) : void;
            FullBody_Land(FullBody_Land: $Ref<UE.PoseLink>) : void;
            FullBody_WalkRun(FullBody_WalkRun: $Ref<UE.PoseLink>) : void;
            GetCharacterABP() : UE.Game.Migrates.Blueprints.ABP_CharacterBase.ABP_CharacterBase_C;
            PhySimulation(InPose: UE.PoseLink, PhySimulation: $Ref<UE.PoseLink>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ABP_XiaoShenBase_C;
            static Load(InName: string): ABP_XiaoShenBase_C;
        
            __tid_ABP_XiaoShenBase_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8F2CE98E4F936319F793A1A944E72044
    namespace Game.Migrates.Blueprints.ABP_XiaoShen_Sword {
        class ABP_XiaoShen_Sword_C extends UE.Game.Migrates.Blueprints.ABP_XiaoShenBase.ABP_XiaoShenBase_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ABP_XiaoShen_Sword_C;
            static Load(InName: string): ABP_XiaoShen_Sword_C;
        
            __tid_ABP_XiaoShen_Sword_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0DF0FDB04EDF11C824DBB6B7029DD89D
    namespace Game.Migrates.Blueprints.ABP_XiaoShen_Unarmed {
        class ABP_XiaoShen_Unarmed_C extends UE.Game.Migrates.Blueprints.ABP_XiaoShenBase.ABP_XiaoShenBase_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ABP_XiaoShen_Unarmed_C;
            static Load(InName: string): ABP_XiaoShen_Unarmed_C;
        
            __tid_ABP_XiaoShen_Unarmed_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: BD12DD374F2A5BA1DA296FB919D6533B
    namespace Game.Migrates.Blueprints.ALI_DCharacter {
        class ALI_DCharacter_C extends UE.AnimLayerInterface {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            FullBody_Idle(FullBody_Idle: $Ref<UE.PoseLink>) : void;
            FullBody_JumpLoop(FullBody_JumpLoop: $Ref<UE.PoseLink>) : void;
            FullBody_JumpStart(FullBody_JumpStart: $Ref<UE.PoseLink>) : void;
            FullBody_Land(FullBody_Land: $Ref<UE.PoseLink>) : void;
            FullBody_WalkRun(FullBody_WalkRun: $Ref<UE.PoseLink>) : void;
            PhySimulation(InPose: UE.PoseLink, PhySimulation: $Ref<UE.PoseLink>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ALI_DCharacter_C;
            static Load(InName: string): ALI_DCharacter_C;
        
            __tid_ALI_DCharacter_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 42A61AE947BA0CD373A532870F600182
    namespace Game.MagicProjectilesVol2.DemoRoom.BluePrint.BP_DemoRoom {
        class BP_DemoRoom_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            Scene1: UE.SceneComponent;
            BaseRoomSize: number;
            SectionWidth: UE.Vector;
            TrimWidth: UE.Vector;
            MirrorRoom: boolean;
            Lights: boolean;
            LightRadius: number;
            Brightness: number;
            DoubleHeight: boolean;
            LoopMesh: UE.StaticMesh;
            OpenRoof: boolean;
            NumberofRooms: number;
            SwitchColor: boolean;
            GlassWalls: boolean;
            PerRoomProperties: TArray<UE.Game.MagicProjectilesVol2.DemoRoom.BluePrint.DemoRoomStruct.DemoRoomStruct>;
            RoomNames: TArray<string>;
            RoomType: TArray<UE.Game.MagicProjectilesVol2.DemoRoom.BluePrint.BP_DemoRoom_Enum.BP_DemoRoom_Enum>;
            FrontDoor: boolean;
            OpenBack: boolean;
            CastShadows: boolean;
            EmptyText: string;
            TotalSegments: number;
            ThisRoomSize: number;
            RoomSizes: TArray<number>;
            OffsetList: TArray<number>;
            Offset: number;
            ThisOffset: number;
            MainLoopIndex: number;
            AddBackWall(RoomSize: number, Offset: number) : void;
            AddClamp(Offset: number, RoomSize: number, Index: number) : void;
            AddLights(Index: number, RoomSize: number, Offset: number) : void;
            AddLoopSections(Scale: UE.Vector, Offset: number, RoomSize: number, Index: number) : void;
            AddOpenTrim(Scale: UE.Vector, Offset: number, RoomSize: number, Index: number) : void;
            AddRoomNames(Index: number, RoomSize: number, Offset: number) : void;
            AddTrim(Scale: UE.Vector, Index: number, RoomSize: number, Offset: number) : void;
            AddWall(Scale: UE.Vector, Offset: number, RoomSize: number, Index: number) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_DemoRoom_C;
            static Load(InName: string): BP_DemoRoom_C;
        
            __tid_BP_DemoRoom_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0A33583F4BE66724A5C7E18124493C22
    namespace Game.MagicProjectilesVol2.DemoRoom.BluePrint.BP_DemoRoom_Enum {
        enum BP_DemoRoom_Enum { Standard, RoofwithHole, RoofOpen, BP_DemoRoom_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6943AFC8409D912B2468F888D9C48A98
    namespace Game.MagicProjectilesVol2.DemoRoom.BluePrint.DemoRoomStruct {
        class DemoRoomStruct {
            constructor();
            constructor(RoomName: string, RoomType: UE.Game.MagicProjectilesVol2.DemoRoom.BluePrint.BP_DemoRoom_Enum.BP_DemoRoom_Enum, OverrideSize: number);
            RoomName: string;
            RoomType: UE.Game.MagicProjectilesVol2.DemoRoom.BluePrint.BP_DemoRoom_Enum.BP_DemoRoom_Enum;
            OverrideSize: number;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_DemoRoomStruct_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8AA68A454A8A3F33F33DC09B76E027F4
    namespace Game.MagicProjectilesVol2.Blueprints.BP_GAP_SpawnVFX {
        class BP_GAP_SpawnVFX_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            CreateHUD: boolean;
            CameraShake_Fire: boolean;
            CameraShakeStrength_Fire: number;
            CameraShake_Hit: boolean;
            CameraShakeStrength_Hit: number;
            FirePoint: UE.Actor;
            VFXs: TArray<UE.Class>;
            CurrentVFX: UE.Class;
            index: number;
            SpawnedVFX: UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C;
            HUD: UE.Game.MagicProjectilesVol2.Blueprints.MagicProjectilesHUD.MagicProjectilesHUD_C;
            CameraShakeFire() : void;
            CameraShakeHit() : void;
            ExecuteUbergraph_BP_GAP_SpawnVFX(EntryPoint: number) : void;
            InpActEvt_A_K2Node_InputKeyEvent_0(Key: UE.Key) : void;
            InpActEvt_D_K2Node_InputKeyEvent_1(Key: UE.Key) : void;
            InpActEvt_SpaceBar_K2Node_InputKeyEvent_2(Key: UE.Key) : void;
            NextVFX() : void;
            PreviousVFX() : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            RefreshVfxName(EpicProjectile: $Nullable<UE.Class>) : void;
            SpawnVFX() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_GAP_SpawnVFX_C;
            static Load(InName: string): BP_GAP_SpawnVFX_C;
        
            __tid_BP_GAP_SpawnVFX_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4B7626E84CC9A2A78786C1A733ADF3BB
    namespace Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile {
        class BP_GAP_UnrealProjectile_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Muzzle: UE.ParticleSystemComponent;
            Hit: UE.ParticleSystemComponent;
            RotatingMovement: UE.RotatingMovementComponent;
            Projectile: UE.ParticleSystemComponent;
            ProjectileMovement: UE.ProjectileMovementComponent;
            ProjectileCollider: UE.SphereComponent;
            DefaultSceneRoot: UE.SceneComponent;
            ["ChangeColor ?"]: boolean;
            Color: UE.LinearColor;
            Scale: UE.Vector;
            VFXProjectile: UE.ParticleSystem;
            VFXMuzzle: UE.ParticleSystem;
            ["VFXHit/Impact"]: UE.ParticleSystem;
            RotationRate: UE.Rotator;
            MuzzleOffset: UE.Vector;
            ["Hit/ImpactOffset"]: UE.Vector;
            ProjectileSpeed: number;
            DelayBeforeDestroying: number;
            ColliderRadius: number;
            WarmUpTime: number;
            LoopTime: number;
            originalLocation: UE.Vector;
            originalVelocity: UE.Vector;
            destroy: boolean;
            ExecuteUbergraph_BP_GAP_UnrealProjectile(EntryPoint: number) : void;
            /*
             *Event when this actor overlaps another actor, for example a player walking into a trigger.
             *For events when objects have a blocking collision, for example a player hitting a wall, see 'Hit' events.
             *@note Components on both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events.
             */
            ReceiveActorBeginOverlap(OtherActor: $Nullable<UE.Actor>) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            SetProjectileTemplateToEmpty() : void;
            SpawnMuzzle() : void;
            SpawnProjectile() : void;
            StopProjectile() : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_GAP_UnrealProjectile_C;
            static Load(InName: string): BP_GAP_UnrealProjectile_C;
        
            __tid_BP_GAP_UnrealProjectile_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 61599A504D4D11F5EBA489BE061E52DB
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_BlackHole01_Orange {
        class BP_Projectile_BlackHole01_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_BlackHole01_Orange_C;
            static Load(InName: string): BP_Projectile_BlackHole01_Orange_C;
        
            __tid_BP_Projectile_BlackHole01_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7CEDF22A4852C7633DE2C8B145EF0992
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_BlackHole01_Purple {
        class BP_Projectile_BlackHole01_Purple_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_BlackHole01_Purple_C;
            static Load(InName: string): BP_Projectile_BlackHole01_Purple_C;
        
            __tid_BP_Projectile_BlackHole01_Purple_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8FC52BAF47A001D78179B7A217FDCA16
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_BlackHole01_Red {
        class BP_Projectile_BlackHole01_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_BlackHole01_Red_C;
            static Load(InName: string): BP_Projectile_BlackHole01_Red_C;
        
            __tid_BP_Projectile_BlackHole01_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9BDE6D7A4AAF2A38110F4484DAB23473
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_ElectricBall01_Green {
        class BP_Projectile_ElectricBall01_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_ElectricBall01_Green_C;
            static Load(InName: string): BP_Projectile_ElectricBall01_Green_C;
        
            __tid_BP_Projectile_ElectricBall01_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0F5A5A434155267BF5BDD78B482611F5
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_ElectricBall01_Red {
        class BP_Projectile_ElectricBall01_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_ElectricBall01_Red_C;
            static Load(InName: string): BP_Projectile_ElectricBall01_Red_C;
        
            __tid_BP_Projectile_ElectricBall01_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2AE9B0804CF932B206039AB4F2E451A7
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_ElectricBall01_Yellow {
        class BP_Projectile_ElectricBall01_Yellow_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_ElectricBall01_Yellow_C;
            static Load(InName: string): BP_Projectile_ElectricBall01_Yellow_C;
        
            __tid_BP_Projectile_ElectricBall01_Yellow_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6EAD44C049BA3F28CCB67692B859D0D2
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball03_Orange {
        class BP_Projectile_Fireball03_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball03_Orange_C;
            static Load(InName: string): BP_Projectile_Fireball03_Orange_C;
        
            __tid_BP_Projectile_Fireball03_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 851D117748AB524FD1FFE6B074E57F23
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball03_Purple {
        class BP_Projectile_Fireball03_Purple_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball03_Purple_C;
            static Load(InName: string): BP_Projectile_Fireball03_Purple_C;
        
            __tid_BP_Projectile_Fireball03_Purple_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 355E2C49401D788F52E0CA99CD207B0C
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball03_Red {
        class BP_Projectile_Fireball03_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball03_Red_C;
            static Load(InName: string): BP_Projectile_Fireball03_Red_C;
        
            __tid_BP_Projectile_Fireball03_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: BFBF219B423A592A1DA66EBAC5638450
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball04_Blue {
        class BP_Projectile_Fireball04_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball04_Blue_C;
            static Load(InName: string): BP_Projectile_Fireball04_Blue_C;
        
            __tid_BP_Projectile_Fireball04_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 904481DA4E22FDB31032E2B424C07153
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball04_Green {
        class BP_Projectile_Fireball04_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball04_Green_C;
            static Load(InName: string): BP_Projectile_Fireball04_Green_C;
        
            __tid_BP_Projectile_Fireball04_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 642BC481439F205CBE53F38C4620D92C
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball04_Orange {
        class BP_Projectile_Fireball04_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball04_Orange_C;
            static Load(InName: string): BP_Projectile_Fireball04_Orange_C;
        
            __tid_BP_Projectile_Fireball04_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 539A1A4D4F698DB33E0009A5E767D2B0
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball05_Green {
        class BP_Projectile_Fireball05_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball05_Green_C;
            static Load(InName: string): BP_Projectile_Fireball05_Green_C;
        
            __tid_BP_Projectile_Fireball05_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 59E0D44B434155FF17081E8C45A89127
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball05_Orange {
        class BP_Projectile_Fireball05_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball05_Orange_C;
            static Load(InName: string): BP_Projectile_Fireball05_Orange_C;
        
            __tid_BP_Projectile_Fireball05_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 764E5EFA4E42533683958681650D8E69
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Fireball05_Violet {
        class BP_Projectile_Fireball05_Violet_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball05_Violet_C;
            static Load(InName: string): BP_Projectile_Fireball05_Violet_C;
        
            __tid_BP_Projectile_Fireball05_Violet_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: BD78DBAE4361913FB6F5EE8CDB4356B8
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Firefrost01_Green {
        class BP_Projectile_Firefrost01_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Firefrost01_Green_C;
            static Load(InName: string): BP_Projectile_Firefrost01_Green_C;
        
            __tid_BP_Projectile_Firefrost01_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1296FEED482B07A1AC9C26A2935A3C61
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Firefrost01_Orange {
        class BP_Projectile_Firefrost01_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Firefrost01_Orange_C;
            static Load(InName: string): BP_Projectile_Firefrost01_Orange_C;
        
            __tid_BP_Projectile_Firefrost01_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 80F654BB46FA7F1758B96F8F6D5F67A7
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Firefrost01_Pink {
        class BP_Projectile_Firefrost01_Pink_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Firefrost01_Pink_C;
            static Load(InName: string): BP_Projectile_Firefrost01_Pink_C;
        
            __tid_BP_Projectile_Firefrost01_Pink_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B7205046422A80B67E08F0BEA6037CD8
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_IceSpike01_Blue {
        class BP_Projectile_IceSpike01_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_IceSpike01_Blue_C;
            static Load(InName: string): BP_Projectile_IceSpike01_Blue_C;
        
            __tid_BP_Projectile_IceSpike01_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2FDED83045628CCF4AE8008403883B69
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_IceSpike01_Orange {
        class BP_Projectile_IceSpike01_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_IceSpike01_Orange_C;
            static Load(InName: string): BP_Projectile_IceSpike01_Orange_C;
        
            __tid_BP_Projectile_IceSpike01_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A60387BD4AFA210FC995DB979585A81B
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_IceSpike01_Purple {
        class BP_Projectile_IceSpike01_Purple_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_IceSpike01_Purple_C;
            static Load(InName: string): BP_Projectile_IceSpike01_Purple_C;
        
            __tid_BP_Projectile_IceSpike01_Purple_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D3405AB84D4C06FE60A8608989059E38
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb01_Green {
        class BP_Projectile_Orb01_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb01_Green_C;
            static Load(InName: string): BP_Projectile_Orb01_Green_C;
        
            __tid_BP_Projectile_Orb01_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 3F7DB1664789A1617C7C09A5D7FB5A2B
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb01_Purple {
        class BP_Projectile_Orb01_Purple_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb01_Purple_C;
            static Load(InName: string): BP_Projectile_Orb01_Purple_C;
        
            __tid_BP_Projectile_Orb01_Purple_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 62A39A6E4D6B5CE73860F680CC7E9A20
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb01_Red {
        class BP_Projectile_Orb01_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb01_Red_C;
            static Load(InName: string): BP_Projectile_Orb01_Red_C;
        
            __tid_BP_Projectile_Orb01_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2DFBEDD845BC175AEAAB36898350E804
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb02_Blue {
        class BP_Projectile_Orb02_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb02_Blue_C;
            static Load(InName: string): BP_Projectile_Orb02_Blue_C;
        
            __tid_BP_Projectile_Orb02_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E618B9724291E058A86F4EA8158A96B7
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb02_Orange {
        class BP_Projectile_Orb02_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb02_Orange_C;
            static Load(InName: string): BP_Projectile_Orb02_Orange_C;
        
            __tid_BP_Projectile_Orb02_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 762F50AB4000CAB9C210A595E9EEE041
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb02_Pink {
        class BP_Projectile_Orb02_Pink_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb02_Pink_C;
            static Load(InName: string): BP_Projectile_Orb02_Pink_C;
        
            __tid_BP_Projectile_Orb02_Pink_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C848290C47532BB73B083097DBCFE457
    namespace Game.Blueprints.TDA_SelectLocation {
        class TDA_SelectLocation_C extends UE.DTargetActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            Location: UE.Vector;
            Hit: boolean;
            ExecuteUbergraph_TDA_SelectLocation(EntryPoint: number) : void;
            InpActEvt_IA_CancelAbility_K2Node_EnhancedInputActionEvent_0(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            InpActEvt_IA_SelectTargetLocation_Click_K2Node_EnhancedInputActionEvent_1(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event to notify blueprints this actor is being deleted or removed from a level.
             */
            ReceiveEndPlay(EndPlayReason: UE.EEndPlayReason) : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TDA_SelectLocation_C;
            static Load(InName: string): TDA_SelectLocation_C;
        
            __tid_TDA_SelectLocation_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: DA06F2554F3D2E83A132768988EAA115
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb03_Blue {
        class BP_Projectile_Orb03_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb03_Blue_C;
            static Load(InName: string): BP_Projectile_Orb03_Blue_C;
        
            __tid_BP_Projectile_Orb03_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9FB9617C4CF83D5CD41AD89A23A5EDFC
    namespace Game.Blueprints.TDA_SelectCharacter {
        class TDA_SelectCharacter_C extends UE.DTargetActor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            ["Hit Actor"]: UE.Actor;
            ExecuteUbergraph_TDA_SelectCharacter(EntryPoint: number) : void;
            InpActEvt_IA_CancelAbility_K2Node_EnhancedInputActionEvent_0(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            InpActEvt_IA_SelectTargetLocation_Click_K2Node_EnhancedInputActionEvent_1(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *Event to notify blueprints this actor is being deleted or removed from a level.
             */
            ReceiveEndPlay(EndPlayReason: UE.EEndPlayReason) : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TDA_SelectCharacter_C;
            static Load(InName: string): TDA_SelectCharacter_C;
        
            __tid_TDA_SelectCharacter_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7F9C88A84AA88A73EFB2CA91C128CBCD
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb03_Green {
        class BP_Projectile_Orb03_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb03_Green_C;
            static Load(InName: string): BP_Projectile_Orb03_Green_C;
        
            __tid_BP_Projectile_Orb03_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 014C9D0F4506E768B6207DB7ADDEEEDF
    namespace Game.Blueprints.OnlineGameFunctionLibrary {
        class OnlineGameFunctionLibrary_C extends UE.BlueprintFunctionLibrary {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static IsFriendOnly(__WorldContext: $Nullable<UE.Object>) : void;
            static IsRoomFull(__WorldContext: $Nullable<UE.Object>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): OnlineGameFunctionLibrary_C;
            static Load(InName: string): OnlineGameFunctionLibrary_C;
        
            __tid_OnlineGameFunctionLibrary_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 3405C50741F9DA4B516B27A3F3E6126C
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb03_Orange {
        class BP_Projectile_Orb03_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb03_Orange_C;
            static Load(InName: string): BP_Projectile_Orb03_Orange_C;
        
            __tid_BP_Projectile_Orb03_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D6F0F8074F2F4CED04BA4CA8547A279C
    namespace Game.Blueprints.E_AnimLayer {
        enum E_AnimLayer { Unarmmed, SwordOneHand, SwordTwoHands, NewEnumerator3, E_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E5786FB743DBBC0D3B93AE8FFE74A7C5
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb04_Blue {
        class BP_Projectile_Orb04_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb04_Blue_C;
            static Load(InName: string): BP_Projectile_Orb04_Blue_C;
        
            __tid_BP_Projectile_Orb04_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FA6411B14334EB34353265A9769A79E2
    namespace Game.Blueprints.BP_TopDownController {
        class BP_TopDownController_C extends UE.DPlayerController {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            PressedThreshold: number;
            FXCursor: UE.NiagaraSystem;
            CachedDestination: UE.Vector;
            MouseMoveTimerHandle: UE.TimerHandle;
            LastMouseLocation: UE.Vector;
            HitResult: UE.HitResult;
            ExecuteUbergraph_BP_TopDownController(EntryPoint: number) : void;
            Follow(Location: UE.Vector) : void;
            GetDAbilitySystemComponent() : UE.DAbilitySystemComponent;
            GetLocationUnderCursor(Hit: $Ref<boolean>, Location: $Ref<UE.Vector>) : void;
            GetLocationUnderFinger(Hit: $Ref<boolean>, Location: $Ref<UE.Vector>) : void;
            InitInputSettings() : void;
            InpActEvt_BackSpace_K2Node_InputKeyEvent_0(Key: UE.Key) : void;
            InpActEvt_Enter_K2Node_InputKeyEvent_1(Key: UE.Key) : void;
            InpActEvt_IA_SetDestination_Click_K2Node_EnhancedInputActionEvent_0(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            InpActEvt_IA_SetDestination_Click_K2Node_EnhancedInputActionEvent_1(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            InpActEvt_IA_SetDestination_Click_K2Node_EnhancedInputActionEvent_2(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            InpActEvt_IA_SetDestination_Touch_K2Node_EnhancedInputActionEvent_3(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            InpActEvt_IA_SetDestination_Touch_K2Node_EnhancedInputActionEvent_4(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            InpActEvt_IA_SetDestination_Touch_K2Node_EnhancedInputActionEvent_5(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            InpActEvt_IA_SetDestination_Touch_K2Node_EnhancedInputActionEvent_6(ActionValue: UE.InputActionValue, ElapsedTime: number, TriggeredTime: number, SourceAction: $Nullable<UE.InputAction>) : void;
            K2_BattleBegin(InCharacter: $Nullable<UE.DCharacter>) : void;
            K2_MyTurn(InCharacter: $Nullable<UE.DCharacter>) : void;
            MouseEventFunction() : void;
            MoveTo(Location: UE.Vector) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *更改游戏操控模式，输入为空时自动切换默认控制
             */
            SetInputMappingContext(_In: $Nullable<UE.InputMappingContext>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_TopDownController_C;
            static Load(InName: string): BP_TopDownController_C;
        
            __tid_BP_TopDownController_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 23F9E71D4C435E0A13B3C8969DCD11FC
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb04_Pink {
        class BP_Projectile_Orb04_Pink_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb04_Pink_C;
            static Load(InName: string): BP_Projectile_Orb04_Pink_C;
        
            __tid_BP_Projectile_Orb04_Pink_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: DC4CBEFB433EC09CE25A499C9E10E647
    namespace Game.Blueprints.BP_TopDownCharacter {
        class BP_TopDownCharacter_C extends UE.DCharacter {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            SpeakBubble: UE.WidgetComponent;
            Camera: UE.CameraComponent;
            SpringArm: UE.SpringArmComponent;
            IsMyTurn: boolean;
            TargetActor: UE.Game.Blueprints.TDA_SelectLocation.TDA_SelectLocation_C;
            EndLocation: UE.Vector;
            TimerHandle_FollowMouse: UE.TimerHandle;
            TimerHandle_SpeakBubble: UE.TimerHandle;
            ClearSpeakBubble() : void;
            EnableFollowMouse(Enable: boolean) : void;
            ExecuteUbergraph_BP_TopDownCharacter(EntryPoint: number) : void;
            InpActEvt_One_K2Node_InputKeyEvent_1(Key: UE.Key) : void;
            InpActEvt_Two_K2Node_InputKeyEvent_0(Key: UE.Key) : void;
            K2_BattleBegin() : void;
            K2_MyTurn() : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *在网络数据初始化和BeginPlay之后执行
             */
            ReceivePostNetInit() : void;
            /*
             *Event called every frame, if ticking is enabled
             */
            ReceiveTick(DeltaSeconds: number) : void;
            Speak(InText: string, Duration: number) : void;
            SwitchAnimLinkLayer(NewParam: boolean) : void;
            Tick_FollowMouse() : void;
            TryActivateAbilityWithTag(AbilityTag: UE.GameplayTag) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_TopDownCharacter_C;
            static Load(InName: string): BP_TopDownCharacter_C;
        
            __tid_BP_TopDownCharacter_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2A08B039492DC4CF98EC0089E1F5D731
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb04_Red {
        class BP_Projectile_Orb04_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb04_Red_C;
            static Load(InName: string): BP_Projectile_Orb04_Red_C;
        
            __tid_BP_Projectile_Orb04_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C97C2AEB4731B98E2C8672956E960812
    namespace Game.Blueprints.BP_GasFunctionLibrary {
        class BP_GasFunctionLibrary_C extends UE.BlueprintFunctionLibrary {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static GetActorFromTargetData(__WorldContext: $Nullable<UE.Object>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_GasFunctionLibrary_C;
            static Load(InName: string): BP_GasFunctionLibrary_C;
        
            __tid_BP_GasFunctionLibrary_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 45F776734B186AA607F2C69283F675D5
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb05_Blue {
        class BP_Projectile_Orb05_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb05_Blue_C;
            static Load(InName: string): BP_Projectile_Orb05_Blue_C;
        
            __tid_BP_Projectile_Orb05_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FB3C697C49239F9EE551D3B8DDB6DD22
    namespace Game.Blueprints.BP_DGameMode {
        class BP_DGameMode_C extends UE.DGameModeBase {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            ExecuteUbergraph_BP_DGameMode(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_DGameMode_C;
            static Load(InName: string): BP_DGameMode_C;
        
            __tid_BP_DGameMode_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 268CC5D749AC967B932B75BE4808B99C
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb05_Green {
        class BP_Projectile_Orb05_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb05_Green_C;
            static Load(InName: string): BP_Projectile_Orb05_Green_C;
        
            __tid_BP_Projectile_Orb05_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C0B599184C2AA123901D708049E31449
    namespace Game.Blueprints.BP_BattleInstance {
        class BP_BattleInstance_C extends UE.TurnBasedBattleInstance {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            Characters: TArray<bigint>;
            ExecuteUbergraph_BP_BattleInstance(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_BattleInstance_C;
            static Load(InName: string): BP_BattleInstance_C;
        
            __tid_BP_BattleInstance_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 0833A21B40DC967AB5C0208FA877DE42
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb05_Orange {
        class BP_Projectile_Orb05_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb05_Orange_C;
            static Load(InName: string): BP_Projectile_Orb05_Orange_C;
        
            __tid_BP_Projectile_Orb05_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 660A32FF4F800411A6A10DA254DA1D5F
    namespace Game.Blueprints.AnimNotify_OnHit {
        class AnimNotify_OnHit_C extends UE.AnimNotify_AbilityFire {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): AnimNotify_OnHit_C;
            static Load(InName: string): AnimNotify_OnHit_C;
        
            __tid_AnimNotify_OnHit_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1CB1A99045EA4A1EC0BC8BB32D5B5597
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb06_Blue {
        class BP_Projectile_Orb06_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb06_Blue_C;
            static Load(InName: string): BP_Projectile_Orb06_Blue_C;
        
            __tid_BP_Projectile_Orb06_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 3D0C0F264AC9EFF025C974B7BDAD21E4
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb06_Green {
        class BP_Projectile_Orb06_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb06_Green_C;
            static Load(InName: string): BP_Projectile_Orb06_Green_C;
        
            __tid_BP_Projectile_Orb06_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: BFB2AC5C4C669BC87499959F3AE31F69
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Orb06_Purple {
        class BP_Projectile_Orb06_Purple_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Orb06_Purple_C;
            static Load(InName: string): BP_Projectile_Orb06_Purple_C;
        
            __tid_BP_Projectile_Orb06_Purple_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6E3BB3334105C934B51A0CBD63442985
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Slash01_Blue {
        class BP_Projectile_Slash01_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Slash01_Blue_C;
            static Load(InName: string): BP_Projectile_Slash01_Blue_C;
        
            __tid_BP_Projectile_Slash01_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F06610824F60C9306047A9A11F6BC541
    namespace Game.Blueprints.AStar.ST_AStarTile {
        class ST_AStarTile {
            constructor();
            constructor(Index: UE.Vector, WorldLocation: UE.Vector, Cost: number);
            Index: UE.Vector;
            WorldLocation: UE.Vector;
            Cost: number;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_ST_AStarTile_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1E7418D742099DC7374A0F958DF9D6C6
    namespace Game.Blueprints.AStar.BP_PC_AStar {
        class BP_PC_AStar_C extends UE.PlayerController {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_BP_PC_AStar(EntryPoint: number) : void;
            InpActEvt_LeftMouseButton_K2Node_InputKeyEvent_1(Key: UE.Key) : void;
            InpActEvt_RightMouseButton_K2Node_InputKeyEvent_0(Key: UE.Key) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_PC_AStar_C;
            static Load(InName: string): BP_PC_AStar_C;
        
            __tid_BP_PC_AStar_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7CE956524D98C13BAF590F93070F5BB2
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Slash01_Green {
        class BP_Projectile_Slash01_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Slash01_Green_C;
            static Load(InName: string): BP_Projectile_Slash01_Green_C;
        
            __tid_BP_Projectile_Slash01_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 52712E3B4F5D57D03AF2C1AC925C9120
    namespace Game.Blueprints.AStar.BP_AStar_Obstacle {
        class BP_AStar_Obstacle_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            StaticMesh: UE.StaticMeshComponent;
            Scene: UE.SceneComponent;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_AStar_Obstacle_C;
            static Load(InName: string): BP_AStar_Obstacle_C;
        
            __tid_BP_AStar_Obstacle_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8659F85C4C5F81483065BF855D91FEEE
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Slash01_Orange {
        class BP_Projectile_Slash01_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Slash01_Orange_C;
            static Load(InName: string): BP_Projectile_Slash01_Orange_C;
        
            __tid_BP_Projectile_Slash01_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: FFFD0C42484AF49056247AA4DC0EEE20
    namespace Game.Blueprints.AStar.BP_AStar_Grid {
        class BP_AStar_Grid_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            Billboard: UE.BillboardComponent;
            Scene: UE.SceneComponent;
            GridWorldLocation: UE.Vector;
            GridWorldSize: UE.Vector2D;
            DebugBoxColor: UE.LinearColor;
            PointColor: UE.LinearColor;
            TileSize: number;
            TileSizeMin: number;
            MapData: TMap<UE.Vector, UE.Game.Blueprints.AStar.ST_AStarTile.ST_AStarTile>;
            CalcuEstimatedCost(Begin: UE.Vector, End: UE.Vector) : number;
            CustomSphereTrace(Location: UE.Vector, TraceChannel: UE.ETraceTypeQuery) : boolean;
            DrawBox(Center: UE.Vector) : void;
            DrawTile() : void;
            FindPath(Begin: UE.Vector, End: UE.Vector) : void;
            GenerateMapData() : void;
            GetTileNeighbours(Index: UE.Vector) : TArray<UE.Game.Blueprints.AStar.ST_AStarTile.ST_AStarTile>;
            GridBottomLeft() : UE.Vector;
            GridTileNumber(X: $Ref<number>, Y: $Ref<number>) : void;
            /*
             *Construction script, the place to spawn components and do other setup.
             *@note Name used in CreateBlueprint function
             */
            UserConstructionScript() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_AStar_Grid_C;
            static Load(InName: string): BP_AStar_Grid_C;
        
            __tid_BP_AStar_Grid_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D6C8E11F4F34E827A05C36AD1A60EEC5
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail01_Green {
        class BP_Projectile_Trail01_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail01_Green_C;
            static Load(InName: string): BP_Projectile_Trail01_Green_C;
        
            __tid_BP_Projectile_Trail01_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 9AA03A4047F46CE4B2D83D979E47C4CC
    namespace Game.Blueprints.GAS.GC_Test {
        class GC_Test_C extends UE.GameplayCueNotify_Static {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            /*
             *Generic Event Graph event that will get called for every event type
             */
            K2_HandleGameplayCue(MyTarget: $Nullable<UE.Actor>, EventType: UE.EGameplayCueEvent, Parameters: UE.GameplayCueParameters) : void;
            /*
             *Called when a GameplayCue with duration is first activated, this will only be called if the client witnessed the activation
             */
            OnActive(MyTarget: $Nullable<UE.Actor>, Parameters: UE.GameplayCueParameters) : boolean;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GC_Test_C;
            static Load(InName: string): GC_Test_C;
        
            __tid_GC_Test_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 68B952D642F6A5AE7469A283279C1A6D
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail01_Orange {
        class BP_Projectile_Trail01_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail01_Orange_C;
            static Load(InName: string): BP_Projectile_Trail01_Orange_C;
        
            __tid_BP_Projectile_Trail01_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F3CDB29F4C30A42E143CC38BC0201E11
    namespace Game.Blueprints.GAS.GA_Test {
        class GA_Test_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Test_C;
            static Load(InName: string): GA_Test_C;
        
            __tid_GA_Test_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B851859E4999FD2219608CAFB9A87458
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail01_Purple {
        class BP_Projectile_Trail01_Purple_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail01_Purple_C;
            static Load(InName: string): BP_Projectile_Trail01_Purple_C;
        
            __tid_BP_Projectile_Trail01_Purple_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2E24E7004DAA81D092400BA6658AD9E1
    namespace Game.Blueprints.GAS.GA_Passive_TakeHit {
        class GA_Passive_TakeHit_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_GA_Passive_TakeHit(EntryPoint: number) : void;
            /*
             *The main function that defines what an ability does.
             * -Child classes will want to override this
             * -This function graph should call CommitAbility
             * -This function graph should call EndAbility
             *
             * Latent_async actions are ok in this graph. Note that Commit and EndAbility calling requirements speak to the K2_ActivateAbility graph.
             * In C++, the call to K2_ActivateAbility() may return without CommitAbility or EndAbility having been called. But it is expected that this
             * will only occur when latent_async actions are pending. When K2_ActivateAbility logically finishes, then we will expect Commit_End to have been called.
             */
            K2_ActivateAbility() : void;
            OnBlendOut_FF58513443F1732CFD9113AA69B71613() : void;
            OnCancelled_FF58513443F1732CFD9113AA69B71613() : void;
            OnCompleted_FF58513443F1732CFD9113AA69B71613() : void;
            OnInterrupted_FF58513443F1732CFD9113AA69B71613() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Passive_TakeHit_C;
            static Load(InName: string): GA_Passive_TakeHit_C;
        
            __tid_GA_Passive_TakeHit_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F6B9B0174EC4757E79822089EE7CA3D7
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail02_Blue {
        class BP_Projectile_Trail02_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail02_Blue_C;
            static Load(InName: string): BP_Projectile_Trail02_Blue_C;
        
            __tid_BP_Projectile_Trail02_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 37A48C4C4E2425393078F280948436C2
    namespace Game.Blueprints.GAS.GA_Passive_Dodge {
        class GA_Passive_Dodge_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_GA_Passive_Dodge(EntryPoint: number) : void;
            /*
             *The main function that defines what an ability does.
             * -Child classes will want to override this
             * -This function graph should call CommitAbility
             * -This function graph should call EndAbility
             *
             * Latent_async actions are ok in this graph. Note that Commit and EndAbility calling requirements speak to the K2_ActivateAbility graph.
             * In C++, the call to K2_ActivateAbility() may return without CommitAbility or EndAbility having been called. But it is expected that this
             * will only occur when latent_async actions are pending. When K2_ActivateAbility logically finishes, then we will expect Commit_End to have been called.
             */
            K2_ActivateAbility() : void;
            OnBlendOut_56DA31D544107773535620B273FCBB3A() : void;
            OnCancelled_56DA31D544107773535620B273FCBB3A() : void;
            OnCompleted_56DA31D544107773535620B273FCBB3A() : void;
            OnInterrupted_56DA31D544107773535620B273FCBB3A() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Passive_Dodge_C;
            static Load(InName: string): GA_Passive_Dodge_C;
        
            __tid_GA_Passive_Dodge_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 5A0DA4DB4392B371769EFCA0D141D9D3
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail02_Green {
        class BP_Projectile_Trail02_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail02_Green_C;
            static Load(InName: string): BP_Projectile_Trail02_Green_C;
        
            __tid_BP_Projectile_Trail02_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6356FCCF4A0DDF826276D1AC0701EF2A
    namespace Game.Blueprints.GAS.GA_Passive_Dead {
        class GA_Passive_Dead_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_GA_Passive_Dead(EntryPoint: number) : void;
            /*
             *The main function that defines what an ability does.
             * -Child classes will want to override this
             * -This function graph should call CommitAbility
             * -This function graph should call EndAbility
             *
             * Latent_async actions are ok in this graph. Note that Commit and EndAbility calling requirements speak to the K2_ActivateAbility graph.
             * In C++, the call to K2_ActivateAbility() may return without CommitAbility or EndAbility having been called. But it is expected that this
             * will only occur when latent_async actions are pending. When K2_ActivateAbility logically finishes, then we will expect Commit_End to have been called.
             */
            K2_ActivateAbility() : void;
            OnBlendOut_70440F3946FB71664CE2FA9173849E8D() : void;
            OnCancelled_70440F3946FB71664CE2FA9173849E8D() : void;
            OnCompleted_70440F3946FB71664CE2FA9173849E8D() : void;
            OnInterrupted_70440F3946FB71664CE2FA9173849E8D() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Passive_Dead_C;
            static Load(InName: string): GA_Passive_Dead_C;
        
            __tid_GA_Passive_Dead_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 086137C14DFE6784E722F5BAC8E122E5
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail02_Red {
        class BP_Projectile_Trail02_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail02_Red_C;
            static Load(InName: string): BP_Projectile_Trail02_Red_C;
        
            __tid_BP_Projectile_Trail02_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 268880E94678304206963381193F543E
    namespace Game.Blueprints.GAS.GA_Melee_A {
        class GA_Melee_A_C extends UE.GA_Melee {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_GA_Melee_A(EntryPoint: number) : void;
            /*
             *The main function that defines what an ability does.
             * -Child classes will want to override this
             * -This function graph should call CommitAbility
             * -This function graph should call EndAbility
             *
             * Latent_async actions are ok in this graph. Note that Commit and EndAbility calling requirements speak to the K2_ActivateAbility graph.
             * In C++, the call to K2_ActivateAbility() may return without CommitAbility or EndAbility having been called. But it is expected that this
             * will only occur when latent_async actions are pending. When K2_ActivateAbility logically finishes, then we will expect Commit_End to have been called.
             */
            K2_ActivateAbility() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Melee_A_C;
            static Load(InName: string): GA_Melee_A_C;
        
            __tid_GA_Melee_A_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: E6578144499D489272D82C9E3DC5D465
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail03_Blue {
        class BP_Projectile_Trail03_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail03_Blue_C;
            static Load(InName: string): BP_Projectile_Trail03_Blue_C;
        
            __tid_BP_Projectile_Trail03_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6236FFA4413AB472C8CE168844537CAB
    namespace Game.Blueprints.GAS.GA_Fireball {
        class GA_Fireball_C extends UE.GA_WithProjectile {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            RuntimeProjectile: UE.Game.Blueprints.GAS.BP_Projectile_Fireball.BP_Projectile_Fireball_C;
            ExecuteUbergraph_GA_Fireball(EntryPoint: number) : void;
            /*
             *根据TargetData, 执行发射逻辑(Server Only)
             */
            FireProjectile(TargetData: UE.GameplayAbilityTargetDataHandle, Caster: $Nullable<UE.Actor>) : boolean;
            /*
             *The main function that defines what an ability does.
             * -Child classes will want to override this
             * -This function graph should call CommitAbility
             * -This function graph should call EndAbility
             *
             * Latent_async actions are ok in this graph. Note that Commit and EndAbility calling requirements speak to the K2_ActivateAbility graph.
             * In C++, the call to K2_ActivateAbility() may return without CommitAbility or EndAbility having been called. But it is expected that this
             * will only occur when latent_async actions are pending. When K2_ActivateAbility logically finishes, then we will expect Commit_End to have been called.
             */
            K2_ActivateAbility() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Fireball_C;
            static Load(InName: string): GA_Fireball_C;
        
            __tid_GA_Fireball_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: DCD5F3A549E29FB42FFD379CAEAC67F5
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail03_Purple {
        class BP_Projectile_Trail03_Purple_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail03_Purple_C;
            static Load(InName: string): BP_Projectile_Trail03_Purple_C;
        
            __tid_BP_Projectile_Trail03_Purple_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A37196144710412178C182847E0E62DC
    namespace Game.Blueprints.GAS.BP_Projectile_Fireball {
        class BP_Projectile_Fireball_C extends UE.DProjectile {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Particle: UE.ParticleSystemComponent;
            Niagara: UE.NiagaraComponent;
            Destination: UE.Vector;
            Ridus: number;
            Callback_OnHit(HitComponent: $Nullable<UE.PrimitiveComponent>, OtherActor: $Nullable<UE.Actor>, OtherComp: $Nullable<UE.PrimitiveComponent>, NormalImpulse: UE.Vector, Hit: UE.HitResult) : void;
            ExecuteUbergraph_BP_Projectile_Fireball(EntryPoint: number) : void;
            /*
             *Event when play begins for this actor.
             */
            ReceiveBeginPlay() : void;
            /*
             *激活函数，网络广播
             */
            ReceiveOnActivateNetMulticast(Params: UE.ProjectileParams) : boolean;
            /*
             *投射物激活，执行在服务器或主机端
             */
            ReceiveOnActivateServerOnly(Params: UE.ProjectileParams) : boolean;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Fireball_C;
            static Load(InName: string): BP_Projectile_Fireball_C;
        
            __tid_BP_Projectile_Fireball_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D22FBE6E41B782A524F042B34AE453B9
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail03_Red {
        class BP_Projectile_Trail03_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail03_Red_C;
            static Load(InName: string): BP_Projectile_Trail03_Red_C;
        
            __tid_BP_Projectile_Trail03_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4ADA0C4A426B42E7B31D69BD6CC15A31
    namespace Game.Blueprints.GAS.Abilities.GA_MoveInPace {
        class GA_MoveInPace_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_MoveInPace_C;
            static Load(InName: string): GA_MoveInPace_C;
        
            __tid_GA_MoveInPace_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: EF797F7643A0C8289C8AE487836E1A1A
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail04_Blue {
        class BP_Projectile_Trail04_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail04_Blue_C;
            static Load(InName: string): BP_Projectile_Trail04_Blue_C;
        
            __tid_BP_Projectile_Trail04_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 257F9E3F4F7747D3595A14A74C232206
    namespace Game.Blueprints.GAS.Abilities.GA_MoveInBattle {
        class GA_MoveInBattle_C extends UE.GA_Move {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_MoveInBattle_C;
            static Load(InName: string): GA_MoveInBattle_C;
        
            __tid_GA_MoveInBattle_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 68C6C4E249FB98D973819B8FB4ACBFE0
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail04_Orange {
        class BP_Projectile_Trail04_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail04_Orange_C;
            static Load(InName: string): BP_Projectile_Trail04_Orange_C;
        
            __tid_BP_Projectile_Trail04_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 650FEDA2486D72945EF2A49EB300D3F0
    namespace Game.Blueprints.GAS.Abilities.GameMachine.GA_Machine_TurnEnd {
        class GA_Machine_TurnEnd_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Machine_TurnEnd_C;
            static Load(InName: string): GA_Machine_TurnEnd_C;
        
            __tid_GA_Machine_TurnEnd_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2CE308B04CBDF1BA66435F8C9C1318DB
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail04_Pink {
        class BP_Projectile_Trail04_Pink_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail04_Pink_C;
            static Load(InName: string): BP_Projectile_Trail04_Pink_C;
        
            __tid_BP_Projectile_Trail04_Pink_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 538F229A40726CB0530BA4B5535B4F34
    namespace Game.Blueprints.GAS.Abilities.GameMachine.GA_Machine_MyTurn {
        class GA_Machine_MyTurn_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Machine_MyTurn_C;
            static Load(InName: string): GA_Machine_MyTurn_C;
        
            __tid_GA_Machine_MyTurn_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 1960CD9F40ADEC58D83C6DA3FBC79B9B
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail05_Orange {
        class BP_Projectile_Trail05_Orange_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail05_Orange_C;
            static Load(InName: string): BP_Projectile_Trail05_Orange_C;
        
            __tid_BP_Projectile_Trail05_Orange_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 97664AD5461D2E98FFF3519300B4F470
    namespace Game.Blueprints.GAS.Abilities.GameMachine.GA_Machine_BattleEnd {
        class GA_Machine_BattleEnd_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Machine_BattleEnd_C;
            static Load(InName: string): GA_Machine_BattleEnd_C;
        
            __tid_GA_Machine_BattleEnd_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 39A657DE4ADD8B97FADAFF93195A5514
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail05_Purple {
        class BP_Projectile_Trail05_Purple_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail05_Purple_C;
            static Load(InName: string): BP_Projectile_Trail05_Purple_C;
        
            __tid_BP_Projectile_Trail05_Purple_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 47D85FD14A718E4E5355708102D42D2D
    namespace Game.Blueprints.GAS.Abilities.GameMachine.GA_Machine_BattleBegin {
        class GA_Machine_BattleBegin_C extends UE.DGameplayAbility {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_GA_Machine_BattleBegin(EntryPoint: number) : void;
            /*
             *The main function that defines what an ability does.
             * -Child classes will want to override this
             * -This function graph should call CommitAbility
             * -This function graph should call EndAbility
             *
             * Latent_async actions are ok in this graph. Note that Commit and EndAbility calling requirements speak to the K2_ActivateAbility graph.
             * In C++, the call to K2_ActivateAbility() may return without CommitAbility or EndAbility having been called. But it is expected that this
             * will only occur when latent_async actions are pending. When K2_ActivateAbility logically finishes, then we will expect Commit_End to have been called.
             */
            K2_ActivateAbility() : void;
            /*
             *Blueprint event, will be called if an ability ends normally or abnormally
             */
            K2_OnEndAbility(bWasCancelled: boolean) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GA_Machine_BattleBegin_C;
            static Load(InName: string): GA_Machine_BattleBegin_C;
        
            __tid_GA_Machine_BattleBegin_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6183B2E1458ED1D25558B99E37A29A34
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Trail05_Red {
        class BP_Projectile_Trail05_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Trail05_Red_C;
            static Load(InName: string): BP_Projectile_Trail05_Red_C;
        
            __tid_BP_Projectile_Trail05_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 25D5DA5940DA8822B5421BB560642632
    namespace Game.Blueprints.GAS.GameplayEffects.GE_MyTurn_Instant {
        class GE_MyTurn_Instant_C extends UE.DGameplayEffect {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GE_MyTurn_Instant_C;
            static Load(InName: string): GE_MyTurn_Instant_C;
        
            __tid_GE_MyTurn_Instant_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 97F5161F437973C20108479911A644BF
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Waterball01_Blue {
        class BP_Projectile_Waterball01_Blue_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Waterball01_Blue_C;
            static Load(InName: string): BP_Projectile_Waterball01_Blue_C;
        
            __tid_BP_Projectile_Waterball01_Blue_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B29B1F71401DC4BE56CC1CB2C86FC92C
    namespace Game.Blueprints.GAS.GameplayEffects.GE_InitAtt_Max {
        class GE_InitAtt_Max_C extends UE.DGameplayEffect {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GE_InitAtt_Max_C;
            static Load(InName: string): GE_InitAtt_Max_C;
        
            __tid_GE_InitAtt_Max_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: D3CDB8104D6102E8BDFC3C8181D31EEF
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Waterball01_Green {
        class BP_Projectile_Waterball01_Green_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Waterball01_Green_C;
            static Load(InName: string): BP_Projectile_Waterball01_Green_C;
        
            __tid_BP_Projectile_Waterball01_Green_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 34FCEF994EC65622FF5E12B5225300C5
    namespace Game.Blueprints.GAS.GameplayEffects.GE_InitAtt_Current {
        class GE_InitAtt_Current_C extends UE.DGameplayEffect {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GE_InitAtt_Current_C;
            static Load(InName: string): GE_InitAtt_Current_C;
        
            __tid_GE_InitAtt_Current_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: BA736EF943E24566FEFE319733DBC28D
    namespace Game.MagicProjectilesVol2.Blueprints.BP_Projectile_Waterball01_Red {
        class BP_Projectile_Waterball01_Red_C extends UE.Game.MagicProjectilesVol2.Blueprints.BP_GAP_UnrealProjectile.BP_GAP_UnrealProjectile_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_Projectile_Waterball01_Red_C;
            static Load(InName: string): BP_Projectile_Waterball01_Red_C;
        
            __tid_BP_Projectile_Waterball01_Red_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 87C9C81C4B382DEA2DA1ABA1D999730E
    namespace Game.Blueprints.GAS.GameplayEffects.GE_Fireball {
        class GE_Fireball_C extends UE.DGameplayEffect {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GE_Fireball_C;
            static Load(InName: string): GE_Fireball_C;
        
            __tid_GE_Fireball_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7E5580844E9AF8519B7B818F780CCADE
    namespace Game.MagicProjectilesVol2.Blueprints.CameraShake01 {
        class CameraShake01_C extends UE.LegacyCameraShake {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CameraShake01_C;
            static Load(InName: string): CameraShake01_C;
        
            __tid_CameraShake01_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 589F25234757BBFA339DC7918640C7E1
    namespace Game.Blueprints.GAS.GameplayEffects.GE_BattleBegin {
        class GE_BattleBegin_C extends UE.DGameplayEffect {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): GE_BattleBegin_C;
            static Load(InName: string): GE_BattleBegin_C;
        
            __tid_GE_BattleBegin_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B44EA3934ABEEE585954489A1A95CA83
    namespace Game.MagicProjectilesVol2.Blueprints.MagicProjectilesHUD {
        class MagicProjectilesHUD_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            VFXname: UE.TextBlock;
            effectName: string;
            SetVfxName(effectName: string) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MagicProjectilesHUD_C;
            static Load(InName: string): MagicProjectilesHUD_C;
        
            __tid_MagicProjectilesHUD_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C5B193D34A27B3DAAC01F484C474D71F
    namespace Game.Characters.Mannequins.Rigs.ABP_Manny_PostProcess {
        class ABP_Manny_PostProcess_C extends UE.AnimInstance {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystemInstance;
            AnimBlueprintExtension_Base: UE.AnimSubsystemInstance;
            AnimGraphNode_Root: UE.AnimNode_Root;
            AnimGraphNode_LinkedInputPose: UE.AnimNode_LinkedInputPose;
            AnimGraphNode_ControlRig: UE.AnimNode_ControlRig;
            AnimGraphNode_PoseDriver_13: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_12: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_11: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_10: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_9: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_8: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_7: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_6: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_5: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_4: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_3: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_2: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_1: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver: UE.AnimNode_PoseDriver;
            AnimGraph(InPose: UE.PoseLink, AnimGraph: $Ref<UE.PoseLink>) : void;
            ExecuteUbergraph_ABP_Manny_PostProcess(EntryPoint: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ABP_Manny_PostProcess_C;
            static Load(InName: string): ABP_Manny_PostProcess_C;
        
            __tid_ABP_Manny_PostProcess_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 4225C208474BA9D8FA69EB82B61F5B92
    namespace Game.Characters.Mannequins.Rigs.ABP_Quinn_PostProcess {
        class ABP_Quinn_PostProcess_C extends UE.AnimInstance {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystemInstance;
            AnimBlueprintExtension_Base: UE.AnimSubsystemInstance;
            AnimGraphNode_Root: UE.AnimNode_Root;
            AnimGraphNode_LinkedInputPose: UE.AnimNode_LinkedInputPose;
            AnimGraphNode_ControlRig: UE.AnimNode_ControlRig;
            AnimGraphNode_PoseDriver_13: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_12: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_11: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_10: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_9: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_8: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_7: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_6: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_5: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_4: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_3: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_2: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver_1: UE.AnimNode_PoseDriver;
            AnimGraphNode_PoseDriver: UE.AnimNode_PoseDriver;
            AnimGraph(InPose: UE.PoseLink, AnimGraph: $Ref<UE.PoseLink>) : void;
            ExecuteUbergraph_ABP_Quinn_PostProcess(EntryPoint: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ABP_Quinn_PostProcess_C;
            static Load(InName: string): ABP_Quinn_PostProcess_C;
        
            __tid_ABP_Quinn_PostProcess_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 14560E2845E3185DC9C1A7B70FBCFF06
    namespace Game.Characters.Mannequins.Rigs.CR_Mannequin_BasicFootIK {
        class CR_Mannequin_BasicFootIK_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ZOffset_L_Target: number;
            ZOffset_R_Target: number;
            ZOffset_L: number;
            ZOffset_R: number;
            ZOffset_Pelvis: number;
            ShouldDoIKTrace: boolean;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CR_Mannequin_BasicFootIK_C;
            static Load(InName: string): CR_Mannequin_BasicFootIK_C;
        
            __tid_CR_Mannequin_BasicFootIK_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C10E259249B1D564A9D1FF83D00F5252
    namespace Game.Characters.Mannequins.Rigs.CR_Mannequin_Body {
        class CR_Mannequin_Body_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            ["L Arm IK Mode"]: boolean;
            ["R Arm IK Mode"]: boolean;
            ["L Leg IK Mode "]: boolean;
            ["R Leg IK Mode"]: boolean;
            ["Spine IK Mode"]: boolean;
            ["Neck IK Mode"]: boolean;
            ["Spine Offsets"]: TArray<UE.Transform>;
            ["Spine Length"]: number;
            ["Neck Length"]: number;
            ["L Arm IK Align"]: boolean;
            ["R Arm IK Align"]: boolean;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CR_Mannequin_Body_C;
            static Load(InName: string): CR_Mannequin_Body_C;
        
            __tid_CR_Mannequin_Body_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 7894A68A4A4DA9101FD9D7A8E0143462
    namespace Game.Characters.Mannequins.Rigs.CR_Mannequin_Procedural {
        class CR_Mannequin_Procedural_C extends UE.ControlRig {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): CR_Mannequin_Procedural_C;
            static Load(InName: string): CR_Mannequin_Procedural_C;
        
            __tid_CR_Mannequin_Procedural_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B5D44033474D81AA6EF33F944907B64F
    namespace Game.Characters.Mannequins.Animations.ABP_Manny {
        class AnimBlueprintGeneratedMutableData extends UE.AnimBlueprintMutableData {
            constructor();
            constructor(__FloatProperty: number);
            __FloatProperty: number;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_AnimBlueprintGeneratedMutableData_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: B5D44033474D81AA6EF33F944907B64F
    namespace Game.Characters.Mannequins.Animations.ABP_Manny {
        class ABP_Manny_C extends UE.AnimInstance {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            __AnimBlueprintMutables: UE.Game.Characters.Mannequins.Animations.ABP_Manny.AnimBlueprintGeneratedMutableData;
            AnimBlueprintExtension_PropertyAccess: UE.AnimSubsystemInstance;
            AnimBlueprintExtension_Base: UE.AnimSubsystemInstance;
            AnimGraphNode_Root: UE.AnimNode_Root;
            AnimGraphNode_TransitionResult_7: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_6: UE.AnimNode_TransitionResult;
            AnimGraphNode_BlendSpacePlayer: UE.AnimNode_BlendSpacePlayer;
            AnimGraphNode_StateResult_5: UE.AnimNode_StateResult;
            AnimGraphNode_SequencePlayer_3: UE.AnimNode_SequencePlayer;
            AnimGraphNode_StateResult_4: UE.AnimNode_StateResult;
            AnimGraphNode_StateMachine_1: UE.AnimNode_StateMachine;
            AnimGraphNode_SaveCachedPose: UE.AnimNode_SaveCachedPose;
            AnimGraphNode_TransitionResult_5: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_4: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_3: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_2: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult_1: UE.AnimNode_TransitionResult;
            AnimGraphNode_TransitionResult: UE.AnimNode_TransitionResult;
            AnimGraphNode_ApplyAdditive: UE.AnimNode_ApplyAdditive;
            AnimGraphNode_UseCachedPose_1: UE.AnimNode_UseCachedPose;
            AnimGraphNode_SequencePlayer_2: UE.AnimNode_SequencePlayer;
            AnimGraphNode_StateResult_3: UE.AnimNode_StateResult;
            AnimGraphNode_SequencePlayer_1: UE.AnimNode_SequencePlayer;
            AnimGraphNode_StateResult_2: UE.AnimNode_StateResult;
            AnimGraphNode_SequencePlayer: UE.AnimNode_SequencePlayer;
            AnimGraphNode_StateResult_1: UE.AnimNode_StateResult;
            AnimGraphNode_UseCachedPose: UE.AnimNode_UseCachedPose;
            AnimGraphNode_StateResult: UE.AnimNode_StateResult;
            AnimGraphNode_StateMachine: UE.AnimNode_StateMachine;
            AnimGraphNode_Slot: UE.AnimNode_Slot;
            AnimGraphNode_ControlRig: UE.AnimNode_ControlRig;
            K2Node_PropertyAccess: UE.Actor;
            __CustomProperty_ShouldDoIKTrace_385011E94C94F6DE70691192D3E0622C: boolean;
            Character: UE.Character;
            MovementComponent: UE.CharacterMovementComponent;
            Velocity: UE.Vector;
            GroundSpeed: number;
            ShouldMove: boolean;
            IsFalling: boolean;
            AnimGraph(AnimGraph: $Ref<UE.PoseLink>) : void;
            /*
             *Executed when the Animation is initialized
             */
            BlueprintInitializeAnimation() : void;
            /*
             *Executed when the Animation is updated
             */
            BlueprintUpdateAnimation(DeltaTimeX: number) : void;
            EvaluateGraphExposedInputs_ExecuteUbergraph_ABP_Manny_AnimGraphNode_ControlRig_385011E94C94F6DE70691192D3E0622C() : void;
            EvaluateGraphExposedInputs_ExecuteUbergraph_ABP_Manny_AnimGraphNode_TransitionResult_305F37BB4A5AD886760B8E99A5C561E1() : void;
            ExecuteUbergraph_ABP_Manny(EntryPoint: number) : void;
            GetDAbilitySystemComponent() : UE.DAbilitySystemComponent;
            NewFunction() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ABP_Manny_C;
            static Load(InName: string): ABP_Manny_C;
        
            __tid_ABP_Manny_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 427BCD034923297F7FE1A0820F9C042A
    namespace Game.Characters.Mannequins.Animations.ABP_Quinn {
        class ABP_Quinn_C extends UE.Game.Characters.Mannequins.Animations.ABP_Manny.ABP_Manny_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            ExecuteUbergraph_ABP_Quinn(EntryPoint: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): ABP_Quinn_C;
            static Load(InName: string): ABP_Quinn_C;
        
            __tid_ABP_Quinn_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 146CCEAA42A58AA619F7B9A36FC1BC3A
    namespace Game.Blueprints.Widgets.WBP_CharacterBattlePanel {
        class WBP_CharacterBattlePanel_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            TextBlock_Hp: UE.TextBlock;
            TextBlock_MoveDistance: UE.TextBlock;
            TimerHandle_Delegate: UE.TimerHandle;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            ExecuteUbergraph_WBP_CharacterBattlePanel(EntryPoint: number) : void;
            InitDelegate() : void;
            OnMoveDistanceChange(V: number) : void;
            OnMoveHeathChange(V: number) : void;
            /*
             *Ticks this widget.  Override in derived classes, but always call the parent implementation.
             *
             *@param  MyGeometry The space allotted for this widget
             *@param  InDeltaTime  Real time passed since last tick
             */
            Tick(MyGeometry: UE.Geometry, InDeltaTime: number) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WBP_CharacterBattlePanel_C;
            static Load(InName: string): WBP_CharacterBattlePanel_C;
        
            __tid_WBP_CharacterBattlePanel_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 6275D2DB4D7F7A5AC1056C9FCB6CDFB3
    namespace Game.Blueprints.Widgets.WidgetsFunctionLibrary {
        class WidgetsFunctionLibrary_C extends UE.BlueprintFunctionLibrary {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            static IsFriendOnly(__WorldContext: $Nullable<UE.Object>) : void;
            static IsRoomFull(__WorldContext: $Nullable<UE.Object>) : void;
            static PopNoitfy(InText: string, Duration: number, Color: UE.LinearColor, __WorldContext: $Nullable<UE.Object>) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WidgetsFunctionLibrary_C;
            static Load(InName: string): WidgetsFunctionLibrary_C;
        
            __tid_WidgetsFunctionLibrary_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: ABD4809847121D36DC0D6F818926977D
    namespace Game.Blueprints.Widgets.WBP_Notify {
        class WBP_Notify_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            Float: UE.WidgetAnimation;
            TextBlock_86: UE.TextBlock;
            LifeTime: number;
            TimerHandle_Duration: UE.TimerHandle;
            /*
             *Called after the underlying slate widget is constructed.  Depending on how the slate object is used
             *this event may be called multiple times due to adding and removing from the hierarchy.
             *If you need a true called-once-when-created event, use OnInitialized.
             */
            Construct() : void;
            EndPlay() : void;
            ExecuteUbergraph_WBP_Notify(EntryPoint: number) : void;
            SetMessage(InText: string, Duration: number, Color: UE.LinearColor) : void;
            SetMessageWithString(InText: string, Duration: number, Color: UE.LinearColor) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WBP_Notify_C;
            static Load(InName: string): WBP_Notify_C;
        
            __tid_WBP_Notify_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 590792EA4CD2A46DC703D08F88896864
    namespace Game.Blueprints.Widgets.WBP_SpeakBubble {
        class WBP_SpeakBubble_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            TextBlock_57: UE.TextBlock;
            SetText(InText: string) : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): WBP_SpeakBubble_C;
            static Load(InName: string): WBP_SpeakBubble_C;
        
            __tid_WBP_SpeakBubble_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
}
