// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNodeSpaceConversions.h"
#include "BoneControllers/AnimNode_ModifyBone.h"
#include "BoneControllers/AnimNode_AnimDynamics.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"

#include "AnimNode_ConstraintMultiple.generated.h"

struct FConstraintPair
{
    FCompactPoseBoneIndex DeformationIndex = FCompactPoseBoneIndex(INDEX_NONE);
    FCompactPoseBoneIndex TargetIndex = FCompactPoseBoneIndex(INDEX_NONE);
};

USTRUCT(BlueprintType)
struct ANIMTOOLS_API FAnimNode_ConstraintMultiple : public FAnimNode_SkeletalControlBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Prefixes)
    FString DeformationPrefix;
    UPROPERTY(EditAnywhere, Category = Prefixes)
    FString TargetPrefix;

public:
    int GetNumOfPairs() const { return Constraints.Num(); }
    
    // FAnimNode_Base interface
    virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;

    // FAnimNode_SkeletalControlBase interface
    virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;
    virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;

private:
    // FAnimNode_SkeletalControlBase interface
    virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;

    TArray<FConstraintPair> Constraints;
};
