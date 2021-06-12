// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNode_ConstraintMultiple.h"

void FAnimNode_ConstraintMultiple::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_SkeletalControlBase::Initialize_AnyThread(Context);
	InitializeBoneReferences(Context.AnimInstanceProxy->GetRequiredBones());
}

void FAnimNode_ConstraintMultiple::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
	for (FConstraintPair Constraint : Constraints)
	{
		const FTransform TargetTransform = Output.Pose.GetComponentSpaceTransform(Constraint.TargetIndex);
		OutBoneTransforms.Add(FBoneTransform(FCompactPoseBoneIndex(Constraint.DeformationIndex), TargetTransform));
	}
}

bool FAnimNode_ConstraintMultiple::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	return !Constraints.IsEmpty();
}

void FAnimNode_ConstraintMultiple::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	// Empty the previous constraints
	Constraints.Empty();

	// Validate the prefixes
	if (DeformationPrefix.Len() <= 0 || TargetPrefix.Len() <= 0)
	{
		return;
	}

	// Get the skeleton
	auto& Skeleton = RequiredBones.GetSkeletonAsset()->GetReferenceSkeleton();

	// Loop through the skeleton's bones
	for (int BoneIndex = 0; BoneIndex < Skeleton.GetNum(); BoneIndex++)
	{
		// Get the current bone's name
		FString BoneName = Skeleton.GetBoneName(BoneIndex).ToString();

		// Ignore the bone if it is not a deformation bone
		if (!BoneName.StartsWith(DeformationPrefix))
		{
			continue;
		}

		// Use the bone's name to look for the target bone and continue if no bone was found
		BoneName.RemoveFromStart(DeformationPrefix);
		int TargetBoneIndex = Skeleton.FindBoneIndex(FName(TargetPrefix + BoneName));
		if (TargetBoneIndex == INDEX_NONE)
		{
			continue;
		}

		// Save the new constraint pair
		Constraints.Add({ FCompactPoseBoneIndex(BoneIndex), FCompactPoseBoneIndex(TargetBoneIndex) });
	}
}
