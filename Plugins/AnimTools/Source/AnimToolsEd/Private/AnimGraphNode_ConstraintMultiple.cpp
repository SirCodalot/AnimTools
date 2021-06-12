// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimGraphNode_ConstraintMultiple.h"
#include "AnimNodeEditModes.h"

#define LOCTEXT_NAMESPACE "AnimTools"

FText UAnimGraphNode_ConstraintMultiple::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return GetControllerDescription();
}

void UAnimGraphNode_ConstraintMultiple::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ReconstructNode();
}

FEditorModeID UAnimGraphNode_ConstraintMultiple::GetEditorMode() const
{
	return FEditorModeID();
}

void UAnimGraphNode_ConstraintMultiple::ValidateAnimNodePostCompile(FCompilerResultsLog& MessageLog, UAnimBlueprintGeneratedClass* CompiledClass, int32 CompiledNodeIndex)
{
	UAnimGraphNode_SkeletalControlBase::ValidateAnimNodePostCompile(MessageLog, CompiledClass, CompiledNodeIndex);
}

FText UAnimGraphNode_ConstraintMultiple::GetControllerDescription() const
{
	return LOCTEXT("Constraint Multiple", "Constraint Multiple");
}

#undef LOCTEXT_NAMESPACE